#!/bin/sh
mkdir -p bin
gcc src/find_min_max.c src/sequential_min_max.c src/utils.c -o bin/task1
