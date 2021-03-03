#include <pthread.h>
#include "qsort-thread.h"
#include "qsort.h"

void* quickSortThread(void* args) {
    threadArgs *arguments = (threadArgs*) args;
    int *a = arguments->arr;
    int p = arguments->p, r = arguments->r;
    if(p < r) {
        int q = partition(a, p, r);

        pthread_t thread;
        // quickSort(a, p, q-1);
        threadArgs args1 = {a, p, q-1}, args2 = {a, q+1, r};
    
        pthread_create(&thread, NULL, &quickSortThread, (void*)&args1);

        quickSortThread((void*) &args2);

        pthread_join(thread, NULL);
    }

    return 0;
}