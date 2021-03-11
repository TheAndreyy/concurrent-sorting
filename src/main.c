#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "functions.h"


int main(int argc, char *argv[]) {
    
    srand(time(NULL));

    int size = 0, *arr = NULL, threadLvl, procLvl;
    bool info = false, show = false;
    long long answer;
    int seed;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'i':                           // show results with whole message
                    info = true;
                    break;
                case 'w':                           // print sorted array
                    show = true;
                    break;
                case 'a':                           // set seed for random number generator
                    seed = atoi(argv[++i]);
                    if(seed <= 0) {
                        printf("Seed should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(4);
                    }
                    srand(seed);
                    break;
                case 's':                           // set size of an array and create it
                    size = atoi(argv[++i]);
                    if(size <= 0) {
                        printf("Array size should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(1);
                    }
                    arr = createArray(size, 0, size*100);
                    if(show)
                        showArray(arr, size);
                    break;
                case 'r':                           // run normal quick sort
                    if(arr == NULL) {
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortRun(arr, size, show);
                    if(!show) {
                        if(info)
                            printf("Time for Quick Sort: %lld us\n", answer);
                        else {
                            printf("%lld ", answer);
                            fflush(stdout);
                        }
                    }

                    break;
                case 't':                           // run quick sort with threads
                    threadLvl = atoi(argv[++i]);
                    if(threadLvl <= 0) {
                        printf("Thread level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(2);
                    }
                    if(arr == NULL) {
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortThreadRun(arr, size, threadLvl, show);
                    if(!show) {
                        if(info)
                            printf("Time for Quick Sort with threads: %lld us\n", answer);
                        else {
                            printf("%lld ", answer);
                            fflush(stdout);
                        }
                    }

                    break;
                case 'p':                           // run quick sort with processes
                    procLvl = atoi(argv[++i]);
                    if(procLvl <= 0) {
                        printf("Process level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(3);
                    }
                    if(arr == NULL) {
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortProcessRun(arr, size, procLvl, show);
                    if(!show) {
                        if(info)
                            printf("Time for Quick Sort with processes: %lld us\n", answer);
                        else {
                            printf("%lld ", answer);
                            fflush(stdout);
                        }
                    }

                    break;
                case 'c':                           // run quick sort with processes and threads
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
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortConcurrentRun(arr, size, procLvl, threadLvl, show);
                    if(!show) {
                        if(info)
                            printf("Time for Quick Sort with processes and threads: %lld us\n", answer);
                        else {
                            printf("%lld ", answer);
                            fflush(stdout);
                        }
                    }

                    break;
                default:
                    printf("Cannot distinguish an operatnion \"%s\"\n", argv[i]);
            }
        }
    }
    if(!info)
        printf("\n");
}