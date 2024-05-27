#!/bin/bash

# Remove existing sfml directory
rm -rf ./lib/sfml

# Determine compiler
if command -v gcc &>/dev/null; then
  compiler="gcc"
elif command -v clang &>/dev/null; then
  compiler="clang"
else
  echo "Error: No compatible compiler (gcc or clang) found."
  exit 1
fi

# Determine architecture
arch=$(uname -m)

echo "Architecture: $arch"
echo "Compiler: $compiler"

# Set sfml_bundle based on compiler and architecture
if [ "$compiler" == "gcc" ]; then
  if [ "$arch" == "x86_64" ]; then
    sfml_bundle="SFML-2.6.1-macOS-clang-64-bit.tar.gz"
  elif [ "$arch" == "arm64" ]; then
    sfml_bundle="SFML-2.6.1-macOS-clang-arm64.tar.gz"
  else
    echo "Error: Unsupported architecture '$arch' for gcc."
    exit 1
  fi
elif [ "$compiler" == "clang" ]; then
  if [ "$arch" == "x86_64" ]; then
    sfml_bundle="SFML-2.6.1-macOS-clang-64-bit.tar.gz"
  elif [ "$arch" == "arm64" ]; then
    sfml_bundle="SFML-2.6.1-macOS-clang-arm64.tar.gz"
  else
    echo "Error: Unsupported architecture '$arch' for clang."
    exit 1
  fi
else
  echo "Error: Unsupported compiler '$compiler' or architecture '$arch'."
  exit 1
fi

echo "Using SFML bundle: $sfml_bundle"

# Create directory for SFML
mkdir -p ./lib/sfml

# Extract SFML bundle
tar -xzvf "./lib/$sfml_bundle" -C "./lib/sfml"
if [ $? -ne 0 ]; then
  echo "Error: Failed to extract SFML bundle."
  exit 1
fi

# Rename extracted directory to versioned directory
mv "./lib/sfml/SFML-2.6.1-macOS-clang-arm64" "./lib/sfml/2.6.1"

# Move required frameworks to Frameworks directory
mv "./lib/sfml/2.6.1/extlibs/FLAC.framework" "./lib/sfml/2.6.1/Frameworks/"
mv "./lib/sfml/2.6.1/extlibs/freetype.framework" "./lib/sfml/2.6.1/Frameworks/"
mv "./lib/sfml/2.6.1/extlibs/ogg.framework" "./lib/sfml/2.6.1/Frameworks/"
mv "./lib/sfml/2.6.1/extlibs/vorbis.framework" "./lib/sfml/2.6.1/Frameworks/"
mv "./lib/sfml/2.6.1/extlibs/vorbisenc.framework" "./lib/sfml/2.6.1/Frameworks/"
mv "./lib/sfml/2.6.1/extlibs/vorbisfile.framework" "./lib/sfml/2.6.1/Frameworks/"

echo "SFML setup completed successfully."
