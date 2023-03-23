#!/usr/bin/bash

mkdir build
cd ./build
cmake ..
cmake --build .
./PacMan
cd ..

