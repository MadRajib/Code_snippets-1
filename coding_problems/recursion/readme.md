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
 1. [Permutation with Spaces](#9-permutation-with-spaces)
 1. [Letter Case Permutation](#10-letter-case-permutation)
 1. [Generate Parentheses](#11-generate-parentheses)
 1. [Print N-bit binary numbers having more 1s than 0s](#12-print-n-bit-binary-numbers-having-more-1s-than-0s)
 1. [Find the Safe Position](#13-find-the-safe-position)

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

### 9. Permutation with Spaces
> Given a string s, you need to print all possible strings that can be made by placing spaces (zero or one) in between them. The output should be printed in sorted increasing order of strings.

```bash
Example 1:

Input:
s = "ABC"
Output: (A B C)(A BC)(AB C)(ABC)
Explanation:
ABC
AB C
A BC
A B C
These are the possible combination of "ABC".

Example 2:

Input:
s = "BBR"
Output: (B B R)(B BR)(BB R)(BBR)
```
Apporach:
    
    * Start with index 1,
Code :

```cpp
class Solution {
  public:

    vector<string> permutation(string s) {
        // Code Here
        vector<string> res;
            
        string sub = "";
        recursion(1, s[0] + sub, s, res);
        
        return res;
    }
    
    void recursion(int i, string sub, string& s, vector<string>& res) {
        if (i >= s.length()) {
            res.push_back(sub);
            return;
        }
        
            
        //add space
        recursion(i + 1, sub + " " + s[i], s, res);
        //not include space
        recursion(i + 1, sub + s[i], s, res);
    }
};
```

### 10. Letter Case Permutation
> Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.
> Return a list of all possible strings we could create. Return the output in any order.

 
```bash
Example 1:

Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]
Example 2:

Input: s = "3z4"
Output: ["3z4","3Z4"]
```

Apporach:

* continiue if digit are seen.

Code:

```cpp
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> res;
        string sub = "";
        recursion(0, sub, s, res);

        return res;
    }

    void recursion(int i , string sub, string& s, vector<string> &res) {
        if (i >= s.length()) {
            res.push_back(sub);
            return;
        }

        if (isdigit(s[i])) {
            recursion(i + 1, sub + s[i], s, res);
            return;
        }


        recursion(i + 1, sub + (char)toupper(s[i]), s, res);
        recursion(i + 1, sub + (char)tolower(s[i]), s, res);
    }
};
```

### 11. Generate Parentheses
> Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

```bash
Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
```
Apporach:

* Total length will be 2*n
* we can choose to add open bracket if less than n
* we can choose to ignore open bracket and add close bracket if close is less than open.  

Code: 

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string sub  = "";
        recursion(0, 0, sub, res, n);

        return res;
    }

    void recursion(int open, int close, string sub, vector<string>& res, int n) {

        if (open + close >= 2*n) {
            res.push_back(sub);
            return;
        }

        if (open < n)
            recursion(open + 1, close, sub + "(", res, n);
        
        if (close < open)
            recursion(open, close + 1, sub + ")", res, n);
    }
};

```

### 12. Print N-bit binary numbers having more 1s than 0s
> Given a positive integer n. Your task is to generate a string list of all n-bit binary numbers where, for any prefix of the number, there are more or an equal number of 1's than 0's. The numbers should be sorted in decreasing order of magnitude.

```bash
Example 1:

Input:  
n = 2
Output: 
{"11", "10"}
Explanation: Valid numbers are those where each prefix has more 1s than 0s:
11: all its prefixes (1 and 11) have more 1s than 0s.
10: all its prefixes (1 and 10) have more 1s than 0s.
So, the output is "11, 10".
Example 2:

Input:  
n = 3
Output: 
{"111", "110", "101"}
Explanation: Valid numbers are those where each prefix has more 1s than 0s.
111: all its prefixes (1, 11, and 111) have more 1s than 0s.
110: all its prefixes (1, 11, and 110) have more 1s than 0s.
101: all its prefixes (1, 10, and 101) have more 1s than 0s.
So, the output is "111, 110, 101".

```
Obervation:

* 1 will always be included. 

Code:

```cpp
class Solution {
  public:
    unordered_map<int, int> mp;
    vector<string> NBitBinary(int n) {
        // Your code goes here
        vector<string> res;
        string sub = "";
        
        recursive(0, 0, sub, res, n);
    
        return res;
    }
    
    
    void recursive(int one, int zero, string s, vector<string>& res, const int n) {
        
       if (zero + one == n) {
            res.push_back(s);
            return;
        }
        
        recursive(one + 1, zero, s + "1", res, n);
        
        if (zero < one)
            recursive(one, zero + 1, s + "0", res, n);
    }
};
```

### 13. Find the Safe Position
> There are n people standing in a circle (numbered clockwise 1 to n) waiting to be executed. The counting begins at point 1 in the circle and proceeds around the circle in a fixed direction (clockwise). In each step, a certain number of people are skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom.
Given the total number of persons n and a number k which indicates that k-1 persons are skipped and kth person is killed in circle. The task is to choose the place in the initial circle so that you are the last one remaining and so survive.

```bash
Example 1:

Input:
n = 2, k = 1
Output:
2
Explanation:
Here, n = 2 and k = 1, then safe position is
2 as the person at 1st position will be killed.
Example 2:

Input:
n = 4, k = 2
Output:
1
Explanation:
The safe position is 1.
```

Step 1. __HYpothesis__:
```bash
solve(n, k) -> safe postion
solve(n - 1, k) -> safe position starting from k + 1 till next kth
```

Step 2: __Induction__:
```bash
solve(n, k):
    //base condition
    // why + (k - 1) boz next elimination will happen from k+th position
    // so whatever is returned from solve(n -1, ..) will have index  k - 1 + location 
    return (k -1 + solve(n - 1, k)) % (n + 1)
```

Step 3: __base__:
```bash
if ( n == 1)
            return 1;
```
code:

```cpp
class Solution {
  public:
    int safePos(int n, int k) {
        // code here
        if (n == 1)
            return 1;
        
        return ((k -1) + safePos(n - 1, k)) % n + 1;
    }
};

```