#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "qsort.h"
#include "functions.h"


int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Enter size of an array\n");
        exit(-1);
    }

    srand(time(NULL));

    int size = atoi(argv[1]);

    int *arr = createArray(size, 0, 100*size);

    showArray(arr, size);

    quickSort(arr, 0, size-1);

    showArray(arr, size);

    free(arr);
}