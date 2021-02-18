#!/bin/sh
mkdir -p bin/shared

gcc -c src/tests.c -o bin/tests.o
gcc bin/tests.o -L../revert_string/bin/shared -lrs -o bin/tests -lbcunit

