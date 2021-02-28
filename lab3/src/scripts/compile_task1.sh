#!/bin/sh
bin_dir="$(dirname $(dirname $(realpath $0)) )/bin"
src_dir="$(dirname $(dirname $(realpath $0)) )/src"
mkdir -p $bin_dir

gcc $src_dir/find_min_max.c $src_dir/sequential_min_max.c $src_dir/utils.c -o $bin_dir/task1
