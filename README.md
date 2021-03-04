# Concurrent Sorting
## Implemenatation and comparison of concurrent sorting
This project is a comparison between normal implementation of quick sort and quick sort implementation with multithreading and multiprocessing,

### How to run a program
To run a program pass 2 argument:
1. As first argument size of an array
2. As second argument at with recursion level Quick Sort should stop calling itself parallelly
3. In the future there will be flags to specify options

Example:
> $ ./output/main 10000 3

### Output
Program prints time (in µs) it took 3 algorithms to sort randomly generated array.
