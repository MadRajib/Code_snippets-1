# Binary Search Problems

### Problems
1. [Binary Search](#1-binary-search)
1. [Order Agonostic Search](#2-order-agonostic-search)
1. [First and Last occurrence of an element](#3-first-and-last-occurrence-of-an-element)


Identification :
* sorted array
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

### 2. Order Agonostic Search
```cpp
// first check
bool accending_order =  arr[0] < arr[1];
```

### 3. First and Last occurrence of an element
> Given a sorted array arr[] with possibly some duplicates, the task is to find the first and last occurrences of an element x in the given array.

Note: If the number x is not found in the array then return both the indices as -1.

```bash
Input : arr[] = [1, 3, 5, 5, 5, 5, 67, 123, 125], x = 5
Output : 2 5
Explanation: First occurrence of 5 is at index 2 and last occurrence of 5 is at index 5

Input : arr[] = [1, 3, 5, 5, 5, 5, 7, 123, 125 ], x = 7
Output : 6 6
Explanation: First and last occurrence of 7 is at index 6

Input: arr[] = [1, 2, 3], x = 4
Output: -1 -1
Explanation: No occurrence of 4 in the array, so, output is [-1, -1]
```

```cpp
vec find_first_occurence (arr, x) {
    int first_index = -1;

    while (s <=  e>) {
        mid =  s + (e - s) / 2;
        if (x == arr[mid]) {
            first_index = mid;
            e =  mid - 1;
        } else if ( x < arr[mid]) {
            e = mid - 1;
        } else {
            s = mid + 1;
        }
    }

    retunr first_index;
}

int find_last_occurence (arr, x) {
    int last_index = -1;

    while (s <=  e>) {
        mid =  s + (e - s) / 2;
        if (x == arr[mid]) {
            last_index = mid;
            s =  mid + 1;
        } else if ( x < arr[mid]) {
            e = mid - 1;
        } else {
            s = mid + 1;
        }
    }

    return last_index;
}
```