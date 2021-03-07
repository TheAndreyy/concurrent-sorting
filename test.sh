#!/bin/bash

# Script that compares number of threads and processes to call in sorting

# that printf isn't printing and error because of , instead . for decimal places
export LC_NUMERIC="en_US.UTF-8"

program="output/main"

size=10000000

sum=0
n=1

echo "Normal quick sort"

for((i=0; i<n; i++));
do
    ((sum+=$(./$program -a 1337 -s $size -r)))
    # echo "$i $sum"
done

printf "%.3f\n" $(echo "$sum / $n" | bc -l)

echo "Recurrency level to stop..."

for lvl in {1..15}
do
    echo "multithreading $lvl"

    sum=0

    for((i=0; i<n; i++));
    do
        ((sum+=$(./$program -s $size -t $lvl)))
    done

    printf "%.3f\n" $(echo "$sum / $n" | bc -l)

    echo "multithreading $lvl"

    sum=0

    for((i=0; i<n; i++));
    do
        ((sum+=$(./$program -s $size -p $lvl)))
    done

    printf "%.3f\n" $(echo "$sum / $n" | bc -l)

done


echo "Concurrent sorting"
echo "Recurrency level to stop"

for lvl in {2..15}
do

    for((plvl=1; plvl<lvl; plvl++));
    do
        echo "multiprocesing $plvl multithreading $((lvl-plvl))"

        sum=0
        for((i=0; i<n; i++));
        do
            ((sum+=$(./$program -s $size -c $plvl $((lvl-plvl)))))
        done
        printf "%.3f\n" $(echo "$sum / $n" | bc -l)

    done

done