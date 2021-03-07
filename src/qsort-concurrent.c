#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "qsort.h"
#include "qsort-thread.h"


void quickSortConcurrent(int *a, int p, int r, int procLvl, int threadLvl) {
    if(p < r) {
        int q = partition(a, p, r);

        if(procLvl-- > 0) {
            pid_t pid;
            if((pid = fork()) == 0) {
                quickSortConcurrent(a, p, q-1, procLvl, threadLvl);
                exit(0);
            }
            else if(pid > 0) {
                quickSortConcurrent(a, q+1, r, procLvl, threadLvl);

                int childStatus;
                wait(&childStatus);
                if(!WIFEXITED(childStatus) || WEXITSTATUS(childStatus)) {
                    printf("Error: Child terminated with code %d!", WEXITSTATUS(childStatus));
                    exit(WEXITSTATUS(childStatus));
                }
            }
            else {
                exit(-2);
            }
        }
        else {
            threadLvl--;
            pthread_t thread;

            threadArgs args1 = {a, p, q-1, threadLvl}, args2 = {a, q+1, r, threadLvl};
        
            pthread_create(&thread, NULL, &quickSortThread, (void*)&args1);

            quickSortThread((void*) &args2);

            pthread_join(thread, NULL);
        }
    }
}