#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "functions.h"


int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Error: Enter two arguments size of an array and at which recursion level to stop calling new threads\n");
        exit(-1);
    }

    srand(time(NULL));

    int size = atoi(argv[1]);

    int *arr = createArray(size, 0, 100*size);


    printf("Time for Quick Sort: %lld us\n", qsortRun(arr, size));

    printf("Time for Quick Sort with threads: %lld us\n", qsortThreadRun(arr, size, atoi(argv[3])));

    printf("Time for Quick Sort with processes: %lld us\n", qsortProcessRun(arr, size, atoi(argv[2])));

    printf("Time for Quick Sort with processes and threads: %lld us\n", qsortConcurrentRun(arr, size, atoi(argv[2]), atoi(argv[3])));

}