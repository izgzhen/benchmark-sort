Benchmark sort
=======

## C++11

From [this post](https://stackoverflow.com/questions/5038895/does-stdsort-implement-quicksort):

> `std::sort` is most likely to use QuickSort, or at least a variation over QuickSort called IntroSort, which "degenerates" to HeapSort when the recursion goes too deep.

## Java8

From [this post](https://www.quora.com/What-is-the-complexity-of-Arrays-sort-in-java-Also-why-isn%E2%80%99t-it-as-efficient-as-quick-sort-in-C-or-C++):

> It (`Arrays.sort`) uses dual-pivot quicksort for primitives, which though better than a standard quicksort could still degrade into a quadratic running time.

## Python3

From [this post](https://stackoverflow.com/questions/10948920/what-algorithm-does-pythons-sorted-use):

> Python uses an algorithm called Timsort

## Questions

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