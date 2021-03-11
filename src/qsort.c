#include "qsort.h"

void quickSort(int a[], int p, int r) {
    if(p < r) {
        int q = partition(a, p, r);
        quickSort(a, p, q-1);
        quickSort(a, q+1, r);
    }
}

int partition(int a[], int p, int r) {
    int x = a[r];                   // split array by last element
    int i = p - 1;
    for(int j = p; j < r; j++) {
        if(a[j] <= x) {
            i++;
            swap(a+i, a+j);
        }
    }
    swap(a+i+1, a+r);
    return i + 1;
}

void swap(int *a, int *b) {
    int x = *a;
    *a = *b;
    *b = x;
}