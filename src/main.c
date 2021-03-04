#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/mman.h>

#include "qsort.h"
#include "functions.h"
#include "qsort-thread.h"
#include "qsort-process.h"


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

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    int *arr3 = (int*) mmap(NULL, size * sizeof(int), protection, visibility, -1, 0);

    memcpy(arr3, arr1, size * sizeof(int));

    struct timeval start, end;


    gettimeofday(&start, NULL);

    quickSort(arr1, 0, size-1);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Time for Quick Sort: %lld us\n", micros);

    free(arr1);


    threadArgs args = {arr2, 0, size-1, atoi(argv[2])};

    gettimeofday(&start, NULL);

    quickSortThread((void*) &args);

    gettimeofday(&end, NULL);

    seconds = (end.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Time for Quick Sort with threads: %lld us\n", micros);

    free(arr2);


    gettimeofday(&start, NULL);


    quickSortProcess(arr3, 0, size-1, atoi(argv[2]));

    gettimeofday(&end, NULL);

    seconds = (end.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Time for Quick Sort with processes: %lld us\n", micros);

    munmap(arr3, size);
}