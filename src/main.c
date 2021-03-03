#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "qsort.h"
#include "functions.h"
#include "qsort-thread.h"


int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Error: Enter size of an array\n");
        exit(-1);
    }

    srand(time(NULL));

    int size = atoi(argv[1]);

    int *arr = createArray(size, 0, 100*size);

    showArray(arr, size);

    // quickSort(arr, 0, size-1);
    threadArgs args = {arr, 0, size-1};
    quickSortThread((void*) &args);

    showArray(arr, size);

    free(arr);
}