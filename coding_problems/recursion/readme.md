# Recursion Problems

### [Aproach](#Aproach)
 1. [Print 1 to N](#1-print-1-to-n)
 1. [Sort an array](#2-sort-an-array)


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

Example: 
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

Example:
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