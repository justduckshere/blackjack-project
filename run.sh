#!/bin/bash

cd build

cmake ..

cmake --build . --clean-first

./blackjack-project