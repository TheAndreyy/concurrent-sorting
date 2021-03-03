#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "qsort.h"
#include "functions.h"
#include "qsort-thread.h"


int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Error: Enter two arguments size of an array and at which recursion level to stop calling new threads\n");
        exit(-1);
    }

    srand(time(NULL));

    int size = atoi(argv[1]);

    int *arr1 = createArray(size, 0, 100*size);
    int *arr2 = (int*) malloc(size * sizeof(int));

    memcpy(arr2, arr1, size * sizeof(int));

    // showArray(arr1, size);
    // showArray(arr2, size);

    struct timeval start, end;


    gettimeofday(&start, NULL);

    quickSort(arr1, 0, size-1);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Time for Quick Sort: %lld us\n", micros);

    threadArgs args = {arr2, 0, size-1, atoi(argv[2])};

    gettimeofday(&start, NULL);

    quickSortThread((void*) &args);

    gettimeofday(&end, NULL);

    seconds = (end.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Time for Quick Sort with threads: %lld us\n", micros);

    // showArray(arr1, size);
    // showArray(arr2, size);

    free(arr1);
    free(arr2);
}