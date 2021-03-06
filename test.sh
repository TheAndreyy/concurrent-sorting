#!/bin/bash

# Script that compares number of threads and processes to call in sorting

# that printf isn't printing and error because of , instead . for decimal places
export LC_NUMERIC="en_US.UTF-8"
tabs 4                           # set tab to be 4 spaces


# Constants
program="output/main"

# size=10000      # size of an array to sort
n=10            # trial number
# tests are repeatet n times to get average of tests
# [n should be at least 25 but tests are taking too long]

for size in 10000 100000 1000000 10000000
do
    echo
    echo
    echo "Array size $size"

    echo
    echo "Normal quick sort"

    for((i=0; i<n; i++));
    do
        ((sum+=$(./$program -s $size -r)))
    done

    printf "%.3f\n" $(echo "$sum / 1000000 / $n" | bc -l)


    echo
    echo "Recurrency level to stop multithreading"
    echo "thread_rec_lvl time"
    echo

    for lvl in {1..15}
    do

        sum=0

        for((i=0; i<n; i++));
        do
            ((sum+=$(./$program -s $size -t $lvl)))
        done

        printf "%d\t%.3f\n" $lvl $(echo "$sum / 1000000 / $n" | bc -l)
    done


    echo
    echo "Recurrency level to stop multiprocessing"
    echo "proc_rec_lvl time"
    echo

    for lvl in {1..15}
    do

        sum=0

        for((i=0; i<n; i++));
        do
            ((sum+=$(./$program -s $size -p $lvl)))
        done

        printf "%d\t%.3f\n" $lvl $(echo "$sum / 1000000 / $n" | bc -l)
    done


    echo
    echo "Concurrent sorting"
    echo "Recurrency level to stop multiprocessing and multithreading"
    echo "proc_rec_lvl thread_rec_lvl time"
    echo

    echo -n -e "nProc/nThreads\t"
    for i in {1..14}
    do
        echo -n -e "$i\t\t"
    done
    echo

    for nProc in {1..14}
    do
        echo -n -e "\t\t$nProc\t"
        nThread=1
        while [ $((nProc+nThread)) -le 15 ]
        do
            sum=0
            for((i=0; i<n; i++));
            do
                ((sum+=$(./$program -s $size -c $nProc $nThread)))
            done
            printf "\t%.3f" $(echo "$sum / 1000000 / $n" | bc -l)
            ((nThread++))
        done
        echo

    done
done

echo
tabs -8
