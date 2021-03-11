#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "qsort-process.h"
#include "qsort.h"


void quickSortProcess(int *a, int p, int r, int level) {
    if(p < r) {
        int q = partition(a, p, r);

        if(level-- > 0) {                           // if recurrency level is 0 stop calling new processes
            pid_t pid;
            if((pid = fork()) == 0) {               // if fork() == 0 that means this is a chid process
                quickSortProcess(a, p, q-1, level);
                exit(0);
            }
            else if(pid > 0) {                      // code for parent process
                quickSortProcess(a, q+1, r, level);

                int childStatus;
                wait(&childStatus);                 // wait for child to finish sorting and get its exit status
                
                if(!WIFEXITED(childStatus) || WEXITSTATUS(childStatus)) {       // if error occured during child execution
                    printf("Error: Child terminated with code %d!", WEXITSTATUS(childStatus));
                    exit(WEXITSTATUS(childStatus));
                }
            }
            else {                                  // if for was unsuccesfull
                exit(-2);
            }
        }
        else {
            quickSort(a, p, q-1);
            quickSort(a, q+1, r);
        }
    }
}