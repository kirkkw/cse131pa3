#!/bin/bash
default=${1:-customtest1}
echo "PA3EXE SOLUTION"

./p3exe -d dumpAST < public_samples/$default.glsl 

echo "********************************************"

echo "OUR SHITTY SOLUTION"
./glc < public_samples/$default.glsl
