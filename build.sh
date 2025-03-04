#!/bin/bash

SCRIPT_DIR=$(dirname "$(realpath "$0")")
cd "$SCRIPT_DIR"

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B ./build/
cd ./build/
cp compile_commands.json ../
make
./raystuff
