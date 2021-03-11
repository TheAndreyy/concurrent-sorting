
// struct that is passed as an argument to qSortThread
typedef struct {
    int *arr;       // pointer to an array
    int p;          // index of first argument to be sorted
    int r;          // last index of an array
    int level;      // at which recurrency level threads shouldn't be called
}threadArgs;

void* quickSortThread(void* args);
// pass pointer to struct threadArgs as an argument