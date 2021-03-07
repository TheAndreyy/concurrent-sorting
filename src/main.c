#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "functions.h"


int main(int argc, char *argv[]) {
    
    srand(time(NULL));

    int size = 0, *arr = NULL, threadLvl, procLvl;
    bool info = false;
    long long answer;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'i':
                    info = true;
                    break;
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
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortRun(arr, size);
                    if(info)
                        printf("Time for Quick Sort: %lld us\n", answer);
                    else {
                        printf("%lld ", answer);
                        fflush(stdout);
                    }

                    break;
                case 't':
                    threadLvl = atoi(argv[++i]);
                    if(threadLvl <= 0) {
                        printf("Thread level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(2);
                    }
                    if(arr == NULL) {
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortThreadRun(arr, size, threadLvl);
                    if(info)
                        printf("Time for Quick Sort with threads: %lld us\n", answer);
                    else {
                    printf("%lld ", answer);
                    fflush(stdout);
                    }

                    break;
                case 'p':
                    procLvl = atoi(argv[++i]);
                    if(procLvl <= 0) {
                        printf("Process level should be an integer bigger then 0, not \"%s\"\n", argv[i]);
                        exit(3);
                    }
                    if(arr == NULL) {
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortProcessRun(arr, size, procLvl);
                    if(info)
                        printf("Time for Quick Sort with processes: %lld us\n", qsortProcessRun(arr, size, procLvl));
                    else {
                        printf("%lld ", answer);
                        fflush(stdout);
                    }

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
                        printf("Array is not initialized yet\n");
                        exit(1);
                    }
                    answer = qsortConcurrentRun(arr, size, procLvl, threadLvl);
                    if(info)
                        printf("Time for Quick Sort with processes and threads: %lld us\n", qsortConcurrentRun(arr, size, procLvl, threadLvl));
                    else {
                        printf("%lld ", answer);
                        fflush(stdout);
                    }

                    break;
                default:
                    printf("Cannot distinquish an operatnion \"%s\"\n", argv[i]);
            }
        }
    }
    if(!info)
        printf("\n");
}