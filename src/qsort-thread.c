#include <pthread.h>
#include "qsort-thread.h"
#include "qsort.h"

void* quickSortThread(void* args) {
    threadArgs *arguments = (threadArgs*) args;                 // arguments to threads are passed by pionter to struct threadArgs
    int *a = arguments->arr;                                    // to make args easier to read
    int p = arguments->p, r = arguments->r, level = arguments->level;
    if(p < r) {
        int q = partition(a, p, r);

        if(level-- > 0) {                                       // if recurrency level is 0 stop calling new threads
            pthread_t thread;

            threadArgs args1 = {a, p, q-1, level}, args2 = {a, q+1, r, level};
        
            pthread_create(&thread, NULL, &quickSortThread, (void*)&args1);

            quickSortThread((void*) &args2);

            pthread_join(thread, NULL);                         // thread has to wait for child thread
        }
        else {
            quickSort(a, p, q-1);
            quickSort(a, q+1, r);
        }
    }

    return NULL;
}