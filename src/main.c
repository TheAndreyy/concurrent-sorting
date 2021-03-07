#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "functions.h"


int main(int argc, char *argv[]) {
    
    srand(time(NULL));

    int size = 0, *arr = NULL, threadLvl, procLvl;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 's':
                    size = atoi(argv[++i]);
                    if(size <= 0) {
                        printf("Array size should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(1);
                    }
                    arr = createArray(size, 0, size*100);
                    break;
                case 'r':
                    if(arr == NULL) {
                        printf("Array is not initializet yet\n");
                        exit(1);
                    }
                    printf("Time for Quick Sort: %lld us\n", 
                        qsortRun(arr, size));

                    break;
                case 't':
                    threadLvl = atoi(argv[++i]);
                    if(threadLvl <= 0) {
                        printf("Thread level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(2);
                    }
                    if(arr == NULL) {
                        printf("Array is not initializet yet\n");
                        exit(1);
                    }
                    printf("Time for Quick Sort with threads: %lld us\n", 
                        qsortThreadRun(arr, size, threadLvl));

                    break;
                case 'p':
                    procLvl = atoi(argv[++i]);
                    if(procLvl <= 0) {
                        printf("Process level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(3);
                    }
                    if(arr == NULL) {
                        printf("Array is not initializet yet\n");
                        exit(1);
                    }
                    printf("Time for Quick Sort with processes: %lld us\n", 
                        qsortProcessRun(arr, size, procLvl));

                    break;
                case 'c':
                    procLvl = atoi(argv[++i]);
                    if(procLvl <= 0) {
                        printf("Process level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(3);
                    }
                    threadLvl = atoi(argv[++i]);
                    if(threadLvl <= 0) {
                        printf("Thread level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(2);
                    }
                    if(arr == NULL) {
                        printf("Array is not initializet yet\n");
                        exit(1);
                    }
                    printf("Time for Quick Sort with processes and threads: %lld us\n", 
                        qsortConcurrentRun(arr, size, procLvl, threadLvl));

                    break;
                default:
                    printf("Cannot distinquish an operatnion \"%s\"\n", argv[i]);
            }
        }
    }
}