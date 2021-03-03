#include <stdlib.h>
#include <stdio.h>


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