#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "qsort-process.h"
#include "qsort.h"


void quickSortProcess(int *a, int p, int r, int level) {
    if(p < r) {
        int q = partition(a, p, r);

        if(level-- > 0) {
            pid_t pid;
            if((pid = fork()) == 0) {
                quickSortProcess(a, p, q-1, level);
                exit(0);
            }
            else if(pid > 0) {
                quickSortProcess(a, q+1, r, level);

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
            quickSort(a, p, q-1);
            quickSort(a, q+1, r);
        }
    }
}