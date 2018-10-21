#!/bin/bash

mkdir -p bin
pushd bin
g++ ../src/tests.cpp -o bin/tests
popd