# Concurrent Sorting
## Implemenatation and comparison of concurrent sorting
This project is a comparison between normal implementation of quick sort and quick sort implementation with multithreading and multiprocessing.

## How to run a program

To run a program use flags to get desired output.

Order of flags is important. If you pass e.g. -w only the arrays of called sorting methods after this flag will be printed.
```bash
./main -s 10000 -r -w -t 3
```
Sorted array for **-r** won't be printed for **-t** will.

### Flags:

* **-s** \<value\>, set size of an array to sort as *value*. Should be called before running any sorting method!
* **-r**, run normal Quick Sort
* **-t** \<value\>, run Quick Sort calling threads to *value* recurrency level
* **-p** \<value\>, run Quick Sort with pararell processes called to *value* recurrency level
* **-c** \<pValue\> \<tValue\>, run Quick Sort calling processes to *pValue* recurrency level, then threads to next *tValue* recurrency levels
* **-i**, show output as whole messages. Good to print output in terminal, without -i flag is better to save output to a file.
* **-w**, show sorted array, time measured for sorting won't be printed
* **-a** \<value\>, to set a seed for generating the same arrays that will be sorted

### Examples:

```bash
./main -s 10000 -i -r -t 3
```
Size of an array will be 10000, program will run normal Quick Sort and Quick Sort with threads (will call thread to 3rd recurrency level), and output time for sorting as whole messages.
```bash
./main -w -s 25000 -c 2 3
```
Size of an array will be 25000 and initial array will be printed. Concurrent Quick Sort will be called, calling new processes to 2nd recurrency level and threads to next 3 levels. Output array of concurrent qsort will be printed.

__For more examples see *test.sh* and *test_correct.sh* files.__

## Testing

1. To compile a program use command *$ make all*, use *$ make tidy* to remove *.o files.
2. Use script *test_correct.sh* to see if all sortings techniques sort correctly.
3. Use script *test.sh* to compare time of sorting for all techniques.

## Results

**Coming soon**
