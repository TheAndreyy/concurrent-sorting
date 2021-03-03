
typedef struct {
    int *arr;
    int p;
    int r;
    int level;
}threadArgs;

void* quickSortThread(void* args);