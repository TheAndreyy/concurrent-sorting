#include <stdbool.h>

int getRandom(int min, int max);

void showArray(int arr[], int size);

int* createArray(int size, int min, int max);
// pass size of array, minimal and maximal value of ellements in array
// array will be filled with elements in range from min to max

int* copyArrayToSharedMemory(int *a, int size);

long long qsortRun(int *a, int size, bool show);

long long qsortThreadRun(int *a, int size, int level, bool show);

long long qsortProcessRun(int *a, int size, int level, bool show);

long long qsortConcurrentRun(int *a, int size, int procLvl, int threadLvl, bool show);
