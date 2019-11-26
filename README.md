Benchmark sort
=======

The task is to sort a vector/array of (pseudo-)randomly generated integers using standard libraries, and measure the spent time with respect to the vector/array size.

The current (counter-intuitive) observation is that **the complexity of all standard sort algorithms has a O(n) complexity**.

1. I am suspicious about the correctness of my benchmark code, but can't find anything wrong with it (if you do, please point it out in issues!)
2. I am investigating this problem in a slow pace, and will keep this document updated until I know what is going wrong.
3. You are welcomed to try out the benchmark code on your machine, discuss about potential reason why this happened, and maybe even contribute additional experiments!

We all thought that as working programmers, we understand `sort`, but we *might not*. This is why I am motivated to investigate this.

Note that I didn't care a lot about theoretical worse case for pseudo-code, since (1) modern hardware plus complicated hybrid algorithm engineering can produce very different thing than what you imagine (2) in production, the data distribution is not always the worst case, sometimes much better.

## Results

|       | std::sort                                           | Arrays.sort                                                  | sorted                                            |
| ----- | --------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------- |
| Best  | ?                                                   | ?                                                            | [O(n)](https://en.wikipedia.org/wiki/Timsort)     |
| Avg   | [O(nlogn)](https://en.wikipedia.org/wiki/Introsort) | ?                                                            | [O(nlogn)](https://en.wikipedia.org/wiki/Timsort) |
| Worst | [O(nlogn)](https://en.wikipedia.org/wiki/Introsort) | [O(nlogn)](https://www.quora.com/What-is-the-complexity-of-Arrays-sort-in-java-Also-why-isn%E2%80%99t-it-as-efficient-as-quick-sort-in-C-or-C++) | [O(nlogn)](https://en.wikipedia.org/wiki/Timsort) |

From our [benchmark](explore.ipynb), it seems that the complexity of all algorithms is O(n), rather than the claimed complexities:

![](c++11.png)
![](java8.png)
![](python3.png)

Why?

NOTE:

- All random numbers are real random (`random_device`, `SecureRandom` and `SystemRandom`).

## C++11

Three algorithms are benchmarked: (1) `std::sort` from STL `<algorithms>` (2) `qsort` from `cstdlib`, and (3) `quickSortBaseline` written by myself:

About `std::sort` (from [this post](https://stackoverflow.com/questions/5038895/does-stdsort-implement-quicksort)):

> `std::sort` is most likely to use QuickSort, or at least a variation over QuickSort called IntroSort, which "degenerates" to HeapSort when the recursion goes too deep.

About `qsort` in `cstdlib` (from [wikipedia](https://en.wikipedia.org/wiki/Qsort)):

> **qsort** is a [C standard library](https://en.wikipedia.org/wiki/C_standard_library) function that implements a [polymorphic](https://en.wikipedia.org/wiki/Polymorphism_(computer_science)) [sorting algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm) for arrays of arbitrary objects according to a user-provided comparison function. It is named after the "quicker sort" algorithm (a [quicksort](https://en.wikipedia.org/wiki/Quicksort) variant due to R. S. Scowen), which was originally used to implement it in the [Unix](https://en.wikipedia.org/wiki/Unix) C library, although the C standard does not require it to implement quicksort.

Since I am using Clang on a Mac, I think that the `qsort` I used is compiled from [this version](https://opensource.apple.com/source/Libc/Libc-1272.250.1/stdlib/FreeBSD/qsort.c.auto.html). It reads like a combination of heap-sort (when hitting recursion limit), insertion sort (when input size is small), and quick sort.

About `quickSortBaseline`, it is [here](./quicksort.hpp), nothing magic.

## Java8

From [this post](https://www.quora.com/What-is-the-complexity-of-Arrays-sort-in-java-Also-why-isn%E2%80%99t-it-as-efficient-as-quick-sort-in-C-or-C++):

> It (`Arrays.sort`) uses dual-pivot quicksort for primitives, which though better than a standard quicksort could still degrade into a quadratic running time.

## Python3

From [this post](https://stackoverflow.com/questions/10948920/what-algorithm-does-pythons-sorted-use):

> Python uses an algorithm called [Timsort](https://en.wikipedia.org/wiki/Timsort)

According to wikipedia,

> **Timsort** is a [hybrid](https://en.wikipedia.org/wiki/Hybrid_algorithm) [stable](https://en.wikipedia.org/wiki/Category:Stable_sorts) [sorting algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm), derived from [merge sort](https://en.wikipedia.org/wiki/Merge_sort) and [insertion sort](https://en.wikipedia.org/wiki/Insertion_sort), designed to perform well on many kinds of real-world data.

## Are there O(n) sorting algorithms *in theory*?

From [this post](https://stackoverflow.com/questions/749585/sorting-in-linear-time):

[pigeonhole sort](http://en.wikipedia.org/wiki/Pigeonhole_sort) or [counting sort](http://en.wikipedia.org/wiki/Counting_sort), as well as [radix sort](http://en.wikipedia.org/wiki/Radix_sort).

[Bucket sort](Wikipedia/Bucket sort) is also linear.

## Related Work

I should not be the first one who observed this. Here are some related posts:

- [C++ 11 sort benchmark](https://solarianprogrammer.com/2012/10/24/cpp-11-sort-benchmark/) by Paul
    - The graphics in this post looks confirming my observations, but the author didn't suspect the observed asymptotic complexity.
- [I Wrote a Faster Sorting Algorithm](https://probablydance.com/2016/12/27/i-wrote-a-faster-sorting-algorithm/) by Malte Skarupke
    - The graphics in this post showed that under `std::uniform_int_distribution`, and observed that `stds::sort` is O(n log n), and claimed that `ska_sort_copy`/`ska_sort` looks like O(n).
    - I didn't read through the comments, but it seems like there is a lot of materials there
- [C++ benchmark – std::vector VS std::list VS std::deque](https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html) by Baptiste Wicht
    - The section about "Sort" seems confirming my observation, but no discussion is given.
- 



## Further Readings

[Engineering a Sort Function](http://citeseer.ist.psu.edu/viewdoc/download;jsessionid=E22D8909B745356EF8EBE86CF6EC0309?doi=10.1.1.14.8162&rep=rep1&type=pdf) by JON L. BENTLEY M. DOUGLAS McILROY:

> We recount the history of a new qsort function for a C library. Our function is clearer, faster and more robust than existing sorts. It chooses partitioning elements by a new sampling scheme; it partitions by a novel solution to Dijkstra’s Dutch National Flag problem; and it swaps efficiently. Its behavior was assessed with timing and debugging testbeds, and with a program to certify performance. The design techniques apply in domains beyond sorting.

