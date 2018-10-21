#!/bin/bash

mkdir -p bin
pushd bin
g++ ../src/main.cpp -o ../bin/main
popd