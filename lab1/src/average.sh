#!/bin/sh
summ=0
count=0
for item in $@; do
	summ=$(expr $summ + $item)
	count=$(expr $count + 1)
done
average=0
[ "$count" -eq "0" ]  || average=$(awk "BEGIN { print $summ / $count}")
echo $count
echo $average
	
