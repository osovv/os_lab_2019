#!/bin/sh
bin_dir="$(dirname $(dirname $(realpath $0)) )/bin"
src_dir="$(dirname $(dirname $(realpath $0)) )/src"
seed=5
array_size=10
echo "seed = $seed, array_size = $array_size"
sh -c "$bin_dir/task1 $seed $array_size"
