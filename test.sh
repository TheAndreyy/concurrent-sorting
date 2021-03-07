#!/bin/bash

# Script that compares number of threads and processes to call in sorting

# that printf isn't printing and error because of , instead . for decimal places
export LC_NUMERIC="en_US.UTF-8"

program="output/main"

size=10000000

sum=0
n=2

echo "Normal quick sort"

for((i=0; i<n; i++));
do
    ((sum+=$(./$program -s $size -r)))
done

printf "%.3f\n" $(echo "$sum / 1000 / $n" | bc -l)
echo

echo "Recurrency level to stop..."
echo "multithreading_level time"
echo

for lvl in {1..15}
do

    sum=0

    for((i=0; i<n; i++));
    do
        ((sum+=$(./$program -s $size -t $lvl)))
    done

    printf "%d %.3f\n" $lvl $(echo "$sum / 1000 / $n" | bc -l)
done

echo "multiprocessing_level time"
echo

for lvl in {1..15}
do

    sum=0

    for((i=0; i<n; i++));
    do
        ((sum+=$(./$program -s $size -p $lvl)))
    done

    printf "%d %.3f\n" $lvl $(echo "$sum / 1000 / $n" | bc -l)
done
echo

echo "Concurrent sorting"
echo "Recurrency level to stop: "
echo "multiprocesing_level multithreading_level time"


for lvl in {2..15}
do

    for((plvl=1; plvl<lvl; plvl++));
    do
        sum=0
        for((i=0; i<n; i++));
        do
            ((sum+=$(./$program -s $size -c $plvl $((lvl-plvl)))))
        done
        printf "%d %d %.3f\n" $plvl $((lvl-plvl)) $(echo "$sum / 1000 / $n" | bc -l)

    done
    echo

done