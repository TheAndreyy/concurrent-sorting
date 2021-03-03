
typedef struct {
    int *arr;
    int p;
    int r;
}threadArgs;

void* quickSortThread(void* args);