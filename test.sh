#!/bin/bash

cmake -S . -B build

cmake --build build --clean-first

cd build && ctest --debug 