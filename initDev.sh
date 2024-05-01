rm -rf ./lib/sfml

if [[ $compiler == *"gcc"* ]] && [ "$arch" = "x86_64" ]; then
  sfml_bundle="SFML-2.6.1-linux-gcc-64-bit.tar.gz"
elif [[ $compiler == *"clang"* ]]; then
  if [ "$arch" = "x86_64" ]; then
    sfml_bundle="SFML-2.6.1-macOS-clang-64-bit.tar.gz"
  elif [ "$arch" = "arm64" ]; then
    sfml_bundle="SFML-2.6.1-macOS-clang-arm64.tar.gz"
  fi
fi

if [ -n "$sfml_bundle" ]; then
  mkdir ./lib/sfml
  tar -xzvf "./lib/$sfml_bundle" -C "./lib/sfml"
  mv "./lib/sfml/${sfml_bundle%.tar.gz}" "./lib/sfml/2.6.1"
  mv "./lib/sfml/2.6.1/extlibs/"{FLAC,freetype,ogg,vorbis,vorbisenc,vorbisfile}.framework "./lib/sfml/2.6.1/Frameworks/"
fi