@echo off

mkdir bin
pushd bin
cl ..\src\tests.cpp
popd