#!/bin/sh
mkdir -p bin/shared
make
LD_LIBRARY_PATH=bin/shared ./bin/server --port 5050 --tnum 4 &
LD_LIBRARY_PATH=bin/shared ./bin/server --port 5051 --tnum 4 &
LD_LIBRARY_PATH=bin/shared ./bin/server --port 5052 --tnum 4 &
LD_LIBRARY_PATH=bin/shared ./bin/server --port 5053 --tnum 4 &
