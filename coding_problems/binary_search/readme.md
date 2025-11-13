# Binary Search Problems

### Problems
1. [Binary Search](#1-binary-search)
1. [Order Agonostic Search](#2-order-agonostic-search)
1. [First and Last occurrence of an element](#3-first-and-last-occurrence-of-an-element)
1. [Count No of Elements in a Sorted Array](#4-count-no-of-elements-in-a-sorted-array)
1. [How many times a S Array is rotated](#5-how-many-times-a-s-array-is-rotated)


Identification :
* sorted array
* Search in log(n)

Apporach:
* find mid.
* if not mid then where to jump left or right, determine the condition

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
Solution: 
```cpp
int find_first_occurence (arr, x) {
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

### 4. Count No of Elements in a Sorted Array
Solution: 
```bash
    return find_last_occurence(arr, x) - find_first_occurence(arr, x) + 1;
```

### 5. How many times a S Array is rotated
> Given a sorted array arr[] (in strictly increasing order) that has been right-rotated k times. A right rotation means the last element is moved to the first position, and the remaining elements are shifted one position to the right. Find the value of k the number of times the array was right-rotated from its originally sorted form.

```bash
Input: arr[] = [15, 18, 2, 3, 6, 12]
Output: 2
Explanation: 
Original sorted array = [2, 3, 6, 12, 15, 18]
After 2 right rotations → [15, 18, 2, 3, 6, 12]  

Input: arr[] = [7, 9, 11, 12, 5]
Output: 4
Explanation: 
Original sorted array = [5, 7, 9, 11, 12]  
After 4 right rotations → [7, 9, 11, 12, 5]

Input: arr[] = [7, 9, 11, 12, 15]
Output: 0
Explanation: Array is already sorted, so k = 0  
```
__Obeservation:__
* Index of the min element gives the rotation number.
* Min elmenet will always be present in unorsted array side.
* 3 cases:
    * 1 2 3 (5) 6 7 8
    * 6 7 8 (1) 2 3 5
    * 5 6 7 (8) 1 2 3
    * 7 8 1 (2) 3 5 6

sol:
```cpp
int find_min(arr) {

    while (s <= e) {
        // if range is sorted then first is the min
        //
        if (A[s] <= A[e])
            return s;

        m = s + (e - s) / 2;
        // if left is large then m is the smallest
        if (m > 0 && A[m] < A[m - 1]) {
            return m;
        }
        // if first half is sorted jump to unsorted
        if (A[s] < A[m])
            s = m + 1;
        // else jump to first half which is not sorted
        else
            e = m - 1;
    }

    return 0;
}

// Better
int find_min(arr) {

    while (s < e) {
        // if range is sorted then first is the min
        // 1 2 3 (5) 6 7 8
        if (A[s] <= A[e])
            return s;

        m = s + (e - s) / 2;
        // if first half is sorted jump to unsorted half
        // 5 6 7 (8) 9 1 2
        if (A[s] < A[m])
            s = m + 1;
        // else jump to first half which is not sorted
        // 7 8 1 (2) 3 5 6
        else
            e = m;
    }

    // s will always point to min element at the end
    return s;
}
```