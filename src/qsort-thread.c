#include <pthread.h>
#include "qsort-thread.h"
#include "qsort.h"

void* quickSortThread(void* args) {
    threadArgs *arguments = (threadArgs*) args;
    int *a = arguments->arr;
    int p = arguments->p, r = arguments->r, level = arguments->level;
    if(p < r) {
        if(level-- > 0) {
            int q = partition(a, p, r);

            pthread_t thread;

            threadArgs args1 = {a, p, q-1, level}, args2 = {a, q+1, r, level};
        
            pthread_create(&thread, NULL, &quickSortThread, (void*)&args1);

            quickSortThread((void*) &args2);

            pthread_join(thread, NULL);
        }
        else {
            int q = partition(a, p, r);

            quickSort(a, p, q-1);
            quickSort(a, q+1, r);
        }
    }

    return NULL;
}