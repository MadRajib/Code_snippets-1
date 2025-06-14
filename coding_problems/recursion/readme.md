# Recursion Problems

### [Aproach](#Aproach)
 1. [Print 1 to N](#1-print-1-to-n)
 1. [Sort an array](#2-sort-an-array)
 1. [Sort an stack](#3-sort-an-stack)
 1. [Delete middle element from a stack](#4-delete-middle-element-of-a-stack)
 1. [Reverse a stack](#5-reverse-a-stack)
 1. [K-th Symbol in Grammar](#6-k-th-symbol-in-grammar)
 1. [Tower of Hanoi](#7-tower-of-hanoi)
 1. [Subsets](#8-subsets)


## Aproach
* In Recursion we will be given some __choices__ on which we have to make some __decisions__.
* Don't think on reducing the input size think about __decision__ first, i/p becomes smaller automatically.
* __Recursive Tree__ -> Representation of __decisions__ taken. -> when we undertand decisions
    * i/p o/p method 

![recursion_tree](recursion_tree.svg)

* __Hypothesis-Induction-Base__ Conditions -> when we understand to make I/P smaller
    * __Hypothesis__ -> What should be the o/p
    * __Induction__  -> How it works is added in induction step
    * __Base condtion__ ->  Smallest valid i/p  or largest invalid input

### 1 Print 1 to N

Step 1. __Hypothesis__:
```bash
print(N)   -> prints 1 to N
Print(N-1) -> prints 1 to N-1
```

Step 2: __Induction__:
```bash
print(N) :
    //base condition
    print(N-1)
    cout << N;
```

Step 3: __base__:
```bash
    if ( N == 0 )
        return;
```

### 2 Sort an array

Step 1. __HYpothesis__:
```bash
sort(arr) -> sort array in accending order.
sort(arr) (removing last element) -> sorts array -1 in accessending order.
insert(arr, elem) -> inserts an element to its correct location in sorted array.
```

Step 2: __Induction__:
```bash
sort(arr):
    //base condition
    elem = rr.pop_back();
    sort(arr)

    insert(arr, elem)

insert(arr, elem):
    //base condition
    _elem = arr.pop_back()
    insert(arr, elem)
    arr.push_back(_elem)
```

Step 3: __base__:
```bash
    ----- sort  -----
    if (arr.size() == 1)
        return;

    ---- insert -----
    if (arr.size() == 0 || arr[arr.size() - 1] < elem):
        arr.push_back(elem)
        return;
```

### 3. Sort an stack
Step 1. __HYpothesis__:
```bash
sort(stk) -> sort stack in accending order.
sort(stk) (removing top) -> sorts stack in accessending order.
insert(stk, elem) -> inserts an element to its correct location in sorted stk.
```

Step 2: __Induction__:
```bash
sort(stk):
    //base condition
    elem = rr.pop();
    sort(stk)

    insert(stk, elem)

insert(stk, elem):
    //base condition
    _elem = stk.pop()
    insert(stk, elem)
    stk.push(_elem)
```

Step 3: __base__:
```bash
    ----- sort  -----
    if (stk.size() == 1)
        return;

    ---- insert -----
    if (stk.size() == 0 || stk.top() < elem):
        stk.push(elem)
        return;
```

### 4. Delete Middle Element of a Stack
Step 1. __HYpothesis__:
```bash
delete(stk, K) -> Delete middle element k is middle element index
delete(stk, k - 1) -> remove the top and delete the midle element
```

Step 2: __Induction__:
```bash
delete(stk, k):
    //base condition
    elem = stk.pop;
    delete(stk, k - 1)
    stk.push(elem)

```

Step 3: __base__:
```bash
    if (stk.size() == 0)
        return;
    else if ( k == 1)
        stk.pop();
        return;

```

### 5. Reverse a stack
Step 1. __HYpothesis__:
```bash
reverse(stk) -> reverses the stack
reverse(stk) -> reverse the stack with top element poped
```

Step 2: __Induction__:
```bash
reverse(stk):
    //base condition
    elem =  stk.pop()
    reverse(stk)

    insert(stk, elem)

insert(stk, elem)
    //base condition
    _elem =  stk.pop()
    insert(stk, elem)
    stk.push(_elem)
```

Step 3: __base__:
```bash
------- reverse ----
    if (stk.size() == 1)
        return;

------ Insert -----
    if (stk.size() == 0)
        stk.push(elem)
        return;

```

### 6. K-th Symbol in Grammar
> We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

> For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.
```bash
Example 1:

Input: n = 1, k = 1
Output: 0
Explanation: row 1: 0
Example 2:

Input: n = 2, k = 1
Output: 0
Explanation: 
row 1: 0
row 2: 01
Example 3:

Input: n = 2, k = 2
Output: 1
Explanation: 
row 1: 0
row 2: 01
```

Observation :

* nth row size will be 2^(n-1)
* if k <= mid length of the row, than the first half is same as n-1 row.
* if k > mid then the second half is just the compliment of n-1 row.

Step 1. __HYpothesis__:
```bash
kthGrammar(n, k) - > return 0/1 at index k at row n
kthGrammar(n - 1, k) - > return 0/1 at index k at row n - 1.
```

Step 2: __Induction__:
```bash
kthGrammar(n, k):
    //base condition
    mid = pow(2, n-1)/2;
    if (k <= mid)
        return kthGrammar(n - 1, k)
    else
        return !kthGrammar(n - 1, k - mid)
```

Step 3: __base__:
```bash
if ( n == 1 || k == 1)
    return 0;
```

### 7. Tower of Hanoi
Observation :

* large plates cannot be kept in top of small plate.
* for n - 1 items, we will consider all the plates other than the lowest plate

```bash
TOH(n, {dst: d, helper: h}) - > Moves n plates from s to d using h
TOH(n - 1, {dst: h, helper:d})  - > Move n - 1 to h then place nth plate to d then move move n-1 to d. 
```

Step 2: __Induction__:
```bash
TOH(n, {dst: d, helper: h})
    //base
    TOH(n - 1, {dst: h, helper: d})
    move(n, d)
    TOH(n - 1, {dst: d, helper: s})
```

Step 3: __base__:
```bash
    if (n == 0)
        return;
```
Code:
```cpp
int towerOfHanoi(int n, int from, int to, int aux) {
        // Your code here
        int count = 0;
        if (n == 0)
            return count;
        
        count += towerOfHanoi(n - 1 , from, aux, to);
        count++;
        count += towerOfHanoi(n - 1 , aux, to, from);
        return count;
}
```
### 8 Subsets
> Given an integer array nums of unique elements, return all possible subsets (the power set).

> The solution set must not contain duplicate subsets. Return the solution in any order.
```bash
Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:

Input: nums = [0]
Output: [[],[0]]
```

Aproach:
    * I/p output 

Code:
```bash
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> subs;

        subset(0, subs, nums, res);

        return res;
    }

    void subset(int i, vector<int>& subs, vector<int>& nums, vector<vector<int>>& res) {

        if (i >= nums.size()) {
            res.push_back(subs);
            return;
        }

        subs.push_back(nums[i]);
        subset(i + 1, subs, nums, res);
        subs.pop_back();
        subset(i + 1, subs, nums, res);
    }
};
```