#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/mman.h>

#include "qsort.h"
#include "functions.h"
#include "qsort-thread.h"
#include "qsort-process.h"
#include "qsort-concurrent.h"


int getRandom(int min, int max) {
    return random() % (max + 1 - min) + min;
}

void showArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* createArray(int size, int min, int max) {

    int *ptr = (int*)malloc(size * sizeof(int));

    for(int i = 0; i < size; i++) {
        ptr[i] = getRandom(min, max);
    }
    return ptr;
}

int* copyArrayToSharedMemory(int *a, int size) {
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    int *arr = (int*) mmap(NULL, size * sizeof(int), protection, visibility, -1, 0);

    memcpy(arr, a, size * sizeof(int));

    return arr;
}

long long qsortRun(int *a, int size, bool show) {

    int *arr = (int*) malloc(size * sizeof(int));
    memcpy(arr, a, size * sizeof(int));     // sorting copy of an array

    struct timeval start, end;              // to measure time of sorting

    gettimeofday(&start, NULL);

    quickSort(arr, 0, size-1);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    if(show)
        showArray(arr, size);

    free(arr);

    return micros;
}

long long qsortThreadRun(int *a, int size, int level, bool show) {

    int *arr = (int*) malloc(size * sizeof(int));
    memcpy(arr, a, size * sizeof(int));

    struct timeval start, end;                      // measure time of sorting

    threadArgs args = {arr, 0, size-1, level};      // arguments to threads are passed as threadArgs

    gettimeofday(&start, NULL);

    quickSortThread((void*) &args);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    if(show)
        showArray(arr, size);

    free(arr);

    return micros;
}

long long qsortProcessRun(int *a, int size, int level, bool show) {

    int *arr = copyArrayToSharedMemory(a, size);    // array has to me in shared mmeory so processes see it

    struct timeval start, end;                      // to measure time of sorting

    gettimeofday(&start, NULL);

    quickSortProcess(arr, 0, size-1, level);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    if(show)
        showArray(arr, size);

    munmap(arr, size);                              // to free shared memory

    return micros;
}

long long qsortConcurrentRun(int *a, int size, int procLvl, int threadLvl, bool show) {

    int *arr = copyArrayToSharedMemory(a, size);    // array has to me in shared mmeory so processes see it

    struct timeval start, end;                      // to measure time of sorting

    gettimeofday(&start, NULL);

    quickSortConcurrent(arr, 0, size-1, procLvl, threadLvl);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    if(show)
        showArray(arr, size);

    munmap(arr, size);                              // to free shared memory

    return micros;
}
