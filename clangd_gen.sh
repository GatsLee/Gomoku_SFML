#!/bin/bash

sfml_path="lib/sfml/2.6.1/include"

if [ ! -d "$sfml_path" ]; then
    echo "SFML library should exists in $sfml_path"
    exit 1
fi

pwd=$(pwd)

echo "CompileFlags:" > .clangd
echo "  Add: [-I$pwd/$sfml_path, -I$pwd/include, -I$pwd/src]" >> .clangd