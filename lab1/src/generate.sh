#!/bin/sh
dd if=/dev/random count=150 bs=1 | od -An -t d2  > numbers.txt
