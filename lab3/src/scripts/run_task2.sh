#!/bin/sh
bin_dir="$(dirname $(dirname $(realpath $0)) )/bin"
seed=5
array_size=10
for i in {1..5}; do
    pnum=$i
    echo "seed = $seed, array_size = $array_size, pnum = $i"
    sh -c "$bin_dir/task2 --seed $seed --array_size $array_size --pnum $pnum"
done
