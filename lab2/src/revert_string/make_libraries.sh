#!/bin/sh
mkdir -p bin/shared
mkdir -p bin/static

gcc -c src/main.c -o bin/main.o

gcc -c src/revert_string.c -o bin/static/revert_string.o
gcc -c -fPIC src/revert_string.c -o bin/shared/revert_string.o

ar rcs bin/static/librs.a bin/static/revert_string.o
gcc bin/main.o -Lbin/static -lrs -o bin/statically-linked

gcc -shared bin/shared/revert_string.o -o bin/shared/librs.so
gcc bin/main.o -Lbin/shared -lrs -o bin/use-shared-library

