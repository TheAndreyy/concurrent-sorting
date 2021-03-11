#include <stdbool.h>

int getRandom(int min, int max);
// returns random number if range [min; max]

void showArray(int arr[], int size);
// prints whole array

int* createArray(int size, int min, int max);
// pass size of array, minimal and maximal value of ellements in array
// array will be filled with elements in range [min; max]

int* copyArrayToSharedMemory(int *a, int size);
// call munmap to free memory when you are done 

// call these functions to test different sorting techniques
// bool show is a flag to print sorted array
long long qsortRun(int *a, int size, bool show);

long long qsortThreadRun(int *a, int size, int level, bool show);

long long qsortProcessRun(int *a, int size, int level, bool show);

long long qsortConcurrentRun(int *a, int size, int procLvl, int threadLvl, bool show);
// concurrent sort is a technique where processes and threads are used