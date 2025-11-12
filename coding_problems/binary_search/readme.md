# Binary Search Problems

### Problems
1. [Binary Search](#1-binary-search)


Identification :
    
* Search in log(n)

### 1. Binary Search


> mid = (s + e) / 2; //Can cause OOB

> mid = (s + (e - s) /2); // handles OOB

```cpp
int BS(int elem)
    // ALGO
    s = 0, e = array_len - 1;
    // if accending order
    while (s <= e) {
        m =  s + (e - 2) /2;
        if (elem == A[m])
            return m;
        else if (elem < A[m])
            e = m - 1;
        else
            s = m + 1;
    }

    // if decending order
    while (s <= e) {
        m =  s + (e - 2) /2;
        if (elem == A[m])
            return m;
        else if (elem < A[m])
            s = m + 1;
        else
            e = m - 1;
    }

return - 1;
```

__Note:__

What if Key is Absent ? 
* *low* will point to the first element greater than the key.
* *low* position where to place the element in the sorted array.