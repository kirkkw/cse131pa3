#!/bin/bash

echo "PA3EXE SOLUTION"

./p3exe < public_samples/$1.glsl 

echo "********************************************"

echo "OUR SHITTY SOLUTION"
./glc < public_samples/$1.glsl
