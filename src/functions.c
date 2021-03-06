#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

long long qsortRun(int *a, int size) {
    int *arr = (int*) malloc(size * sizeof(int));
    memcpy(arr, a, size * sizeof(int));

    struct timeval start, end;

    gettimeofday(&start, NULL);

    quickSort(arr, 0, size-1);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    free(arr);

    return micros;
}

long long qsortThreadRun(int *a, int size, int level) {

    int *arr = (int*) malloc(size * sizeof(int));
    memcpy(arr, a, size * sizeof(int));

    struct timeval start, end;

    threadArgs args = {arr, 0, size-1, level};

    gettimeofday(&start, NULL);

    quickSortThread((void*) &args);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    free(arr);

    return micros;
}

long long qsortProcessRun(int *a, int size, int level) {

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    int *arr = (int*) mmap(NULL, size * sizeof(int), protection, visibility, -1, 0);

    memcpy(arr, a, size * sizeof(int));

    struct timeval start, end;

    gettimeofday(&start, NULL);

    quickSortProcess(arr, 0, size-1, level);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    munmap(arr, size);

    return micros;
}

long long qsortConcurrentRun(int *a, int size, int procLvl, int threadLvl) {

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    int *arr = (int*) mmap(NULL, size * sizeof(int), protection, visibility, -1, 0);

    memcpy(arr, a, size * sizeof(int));

    struct timeval start, end;

    gettimeofday(&start, NULL);

    quickSortConcurrent(arr, 0, size-1, procLvl, threadLvl);

    gettimeofday(&end, NULL);

    long long seconds = (end.tv_sec - start.tv_sec);
    long long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    munmap(arr, size);

    return micros;
}