#!/bin/bash

# Script that check if algorithms sort correctly - the same as classical quick sort
# Programs save sorted arrays to a file then hash of these files are compared
# if hash is the same algorithms work properly (for sha256 conflicts are quite rare)

# name of a program to run
program="output/main"

# files to save output of a program
file1="output/resault1"
file2="output/resault2"
file3="output/resault3"
file4="output/resault4"

# size of an array to sort
size=10000000
# set the same seed for every sorting technique
seed=$RANDOM

echo "Running every sorting technique..."

# Classical quick sort algorithm
./$program -a $seed -s $size -w -r > $file1

# Quick sort using threads
./$program -a $seed -s $size -w -t 4 > $file2

# Quick sort using processes
./$program -a $seed -s $size -w -p 4 > $file3

# Quick sort using processes and threads
./$program -a $seed -s $size -w -c 2 2 > $file4


echo "Comparing resaults of sorting for every algorithm"

shasum -a 256 $file1 $file2 $file3 $file4

# removing files with output
rm $file1 $file2 $file3 $file4