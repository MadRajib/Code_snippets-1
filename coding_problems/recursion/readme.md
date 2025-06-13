# Recursion Problems

### [Aproach](#Aproach)
 1. [Print 1 to N](#1-print-1-to-n)
 1. [Sort an array](#2-sort-an-array)
 1. [Sort an stack](#3-sort-an-stack)
 1. [Delete middle element from a stack](#4-delete-middle-element-of-a-stack)
 1. [Reverse a stack](#5-reverse-a-stack)


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

    elem = rr.pop_back();
    sort(arr)

    insert(arr, elem)

insert(arr, elem):
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

    elem = rr.pop();
    sort(stk)

    insert(stk, elem)

insert(stk, elem):
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
    elem =  stk.pop()
    reverse(stk)

    insert(stk, elem)

insert(stk, elem)
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