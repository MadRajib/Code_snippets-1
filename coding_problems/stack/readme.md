# Stack Problems

1. [Nearest Greater to right](#1-nearest-greater-to-right)
1. [Nearest Greater to left](#2-nearest-greater-to-left)
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

### 1. Nearest Greater to right
> Given an array arr[ ] of integers, the task is to find the next greater element for each element of the array in order of their appearance in the array. Next greater element of an element in the array is the nearest element on the right which is greater than the current element.
If there does not exist next greater of current element, then next greater element for current element is -1. For example, next greater of the last element is always -1.

```bash
Examples

Input: arr[] = [1, 3, 2, 4]
Output: [3, 4, 4, -1]
Explanation: The next larger element to 1 is 3, 3 is 4, 2 is 4 and for 4, since it doesn't exist, it is -1.

Input: arr[] = [6, 8, 0, 1, 3]
Output: [8, -1, 1, 3, -1]
Explanation: The next larger element to 6 is 8, for 8 there is no larger elements hence it is -1, for 0 it is 1 , for 1 it is 3 and then for 3 there is no larger element on right and hence -1.

Input: arr[] = [10, 20, 30, 50]
Output: [20, 30, 50, -1]
Explanation: For a sorted array, the next element is next greater element also except for the last element.

Input: arr[] = [50, 40, 30, 10]
Output: [-1, -1, -1, -1]
Explanation: There is no greater element for any of the elements in the array, so all are -1.
```

Apporach 1

* store elements in the stack from last to first i.e first will be on top
* iterate from first:
    >*  pop stack if smaller in top \
    >* -1 is stack empty \
    >*  else stack top is next greater element

Code: 
```cpp
    stack<long long> stk;
    vector<long long> res;

    for (int i = n - 1; i >= 0; i--)
        stk.push(arr[i])

    for (int i = 0; i < n; i++) {
        while (!stk.empty() && stk.top() < arr[i])
            stk.pop();

        if (stk.empty())
            res.push_back(-1);
        else
            res.push_back(stk.top())
    }

    return res;
```
Approach 2:

* Start from last then two iteration can be coupled together
* store only the greater element from last to first

Code: 
```cpp
vector <long long> nextLargerElement(long long arr[], int n){
    
    stack<long long> stk;
    vector<long long> res;
    
    for(int i = n-1; i>=0; i--){
        
        while(!stk.empty() && stk.top() < arr[i]){
            stk.pop();
        }
        
        if(stk.empty()){
            res.push_back(-1);
        }else{
            res.push_back(stk.top());
        }
        stk.push(arr[i]);
    }
    
    // return the reverse res
    return reverse(res.begin(), res.end());
}
```

### 2. Nearest Greater to left

```cpp
vector <long long> prevLargerElement(long long arr[], int n){
    
    stack<long long> stk;
    vector<long long> res;
    
    for(int i = 0; i < n; i++){
        
        while(!stk.empty() && stk.top() < arr[i]){
            stk.pop();
        }
        
        if(stk.empty()){
            res.push_back(-1);
        }else{
            res.push_back(stk.top());
        }
        stk.push(arr[i]);
    }
    
    // return the reverse res
    return res;
}

```

### 3. Nearest Smaller to left

```cpp
vector <long long> prevSmallerElement(long long arr[], int n){
    
    stack<long long> stk;
    vector<long long> res;
    
    for(int i = 0; i < n; i++){
        
        while(!stk.empty() && stk.top() > arr[i]){
            stk.pop();
        }
        
        if(stk.empty()){
            res.push_back(-1);
        }else{
            res.push_back(stk.top());
        }
        stk.push(arr[i]);
    }
    
    // return the reverse res
    return res;
}

```
### 4. Nearest Smaller to right
```cpp
vector <long long> nextSmallerElement(long long arr[], int n){
    
    stack<long long> stk;
    vector<long long> res;
    
    for(int i = n-1; i>=0; i--){
        
        while(!stk.empty() && stk.top() > arr[i]){
            stk.pop();
        }
        
        if(stk.empty()){
            res.push_back(-1);
        }else{
            res.push_back(stk.top());
        }
        stk.push(arr[i]);
    }
    
    // return the reverse res
    return reverse(res.begin(), res.end());
}
```

### 5. Stock Span Problem
> The stock span problem is a financial problem where we have a series of daily price quotes for a stock and we need to calculate the span of stock price for all days. The span arr[i] of the stocks price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the price of the stock on the given day is less than or equal to its price on the current day.

```bash
Examples:

Input: arr[] = [100, 80, 60, 70, 60, 75, 85]
Output: [1, 1, 1, 2, 1, 4, 6]
Explanation: Traversing the given input span 100 is greater than equal to 100 and there are no more elements behind it so the span is 1, 80 is greater than equal to 80 and smaller than 100 so the span is 1, 60 is greater than equal to 60 and smaller than 80 so the span is 1, 70 is greater than equal to 60,70 and smaller than 80 so the span is 2 and so on.  Hence the output will be 1 1 1 2 1 4 6.

Input: arr[] = [10, 4, 5, 90, 120, 80]
Output: [1, 1, 2, 4, 5, 1]
Explanation: Traversing the given input span 10 is greater than equal to 10 and there are no more elements behind it so the span is 1, 4 is greater than equal to 4 and smaller than 10 so the span is 1, 5 is greater than equal to 4,5 and smaller than 10 so the span is 2,  and so on. Hence the output will be 1 1 2 4 5 1.
```

Apporach:

* Nearest largest to the left
* save index with the element on to the stack using pair/tuple
```cpp
class Solution {
  public:
    vector<int> calculateSpan(vector<int>& arr) {
        // write code here
        stack<pair<int, int>> stk;
        vector<int> res;
        
        for (int i = 0; i < arr.size(); i++) {
            while(!stk.empty() && (stk.top().first <= arr[i]))
                stk.pop();
            
            if (stk.empty())
                res.push_back(i + 1);
            else
                res.push_back(i - stk.top().second);
                
            stk.push({arr[i], i});
        }
        
        return res;
    }
};
```