# Stack Problems

1. [Nearest Greater to left](#1-nearest-greater-to-left)
1. [Nearest Greater to right](#2-nearest-greater-to-right)
1. [Nearest Smaller to left](#3-nearest-smaller-to-left)
1. [Nearest Smaller to right](#4-nearest-smaller-to-right)
1. [Stock Span Problem](#5-stock-span-problem)
1. [Maximum Area of Histogram](#6-maximum-area-of-histogram)
1. [Rain Water Trapping](#7-rain-water-trapping)
1. [Implementing min stack](#9-implementing-min-stack)
1. [Implementing stack using heap](#10-implementing-stack-using-heap)
1. [Longest Valid Parenthesis](#11-longest-valid-parenthesis)

Identification

* Array
* O(n^2) : brute force
> Where j is dependent on i
```cpp
for (int i=0; i < n; i++)
    for (int j=0; j< i; j++)

j -> 0 to i : j++
j -> i to 0 : j--
j -> i to n : j++
j -> n to i : j--
```