# Dynamic Programing

- Nothing but enhenced Recursion
- Overlayping recursions [work might be already done] 
- Asks for optimal ouput.
- DP = recursion + storage

Knapsack Problem
    - Fractional Knapsack : GREEDY
    - 0-1 Knapsack : DP
    - Unbouned Knapsack : We can fill one items any no of times

1. [0-1 knapsack problem](#0-1-knapsack-problem)
    - [Subset sum](#subset-sum)
    - [Equal sum partition](#equal-sum-partition)
    - [Count of subset sum](#count-of-subset-sum)
    - [Min subset sum diff](#min-subset-sum-diff)
    - [Count the number of subset with a given difference](#count-the-number-of-subset-with-a-given-difference)
    - [Target sum](#target-sum)
### 0-1 knapsack Problem
> Given two arrays, val[] and wt[], where each element represents the value and weight of an item respectively, and an integer W representing the maximum capacity of the knapsack (the total weight it can hold).

The task is to put the items into the knapsack such that the total value obtained is maximum without exceeding the capacity W.

```bash
Input: W = 4, val[] = [1, 2, 3], wt[] = [4, 5, 1]
Output: 3
Explanation: Choose the last item, which weighs 1 unit and has a value of 3.

Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6] 
Output: 0
Explanation: Every item has a weight exceeding the knapsack's capacity (3).

Input: W = 5, val[] = [10, 40, 30, 50], wt[] = [5, 4, 2, 3] 
Output: 80
Explanation: Choose the third item (value 30, weight 2) and the last item (value 50, weight 3) for a total value of 80.
```
Identification:
    - Optimal ask ? yes
    - Choices ? Yes
Apporach:
    - first Build a recursive apporach
        - Build a choice diagram
    - second memoization the recursion

Recursion:
```cpp
IP = WT[], VAL[]
MW

// n -> of items
// w -> bag capacity
class Solution {
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        return rr(wt, val, 0, W);
    }
    
    int rr(vector<int> &wt, vector<int> &val, int i, int w) {
        // base condition
        if (i >= wt.size() || w == 0)
            return 0;
        
        // decision tree
        if (wt[i] <= w) {
            // take the weight or skip the weight
            return max (   rr(wt, val, i + 1, w - wt[i]) + val[i],
                    rr(wt, val, i + 1, w));
        } else {
            // check the next weight
            return rr(wt, val, i + 1, w);
        }
    }
};
```

Memoisation:
```cpp
class Solution {
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        
        vector<vector<int>> t(wt.size(), vector<int>(W + 1, -1));
        
        return rr(wt, val, 0, W, t);;
    }
    
    int rr(vector<int> &wt, vector<int> &val, int i, int w, vector<vector<int>> &t) {
        // base condition
        if (i >= wt.size() || w == 0)
            return 0;
            
        if (t[i][w] != -1)
            return t[i][w];
        
        // decision tree
        if (wt[i] <= w) {
            // take the weight or skip the weight
            t[i][w] =  max (   rr(wt, val, i + 1, w - wt[i], t) + val[i],
                    rr(wt, val, i + 1, w, t));
                    
            return t[i][w];
        } else {
            // check the next weight
            t[i][w] = rr(wt, val, i + 1, w, t);
            return t[i][w];
        }
    }
};
```

Bottom Up approach
```cpp
int knapsack(int W, vector<int> &val, vector<int> &wt) {
        
        vector<vector<int>> t(wt.size() + 1, vector<int>(W + 1, 0));
        
        // base condition
        // i == n all 0
        // w == 0
        for (int j = 0; j<= W; j++)
            t[wt.size()][j] = 0;
        
        for (int i = 0; i <= wt.size(); i++)
            t[i][0] = 0;
        
        // from btm up, since in recurion last ones are filled first
        for (int i = wt.size() - 1; i >= 0; i--) {
            for (int w = 0; w <= W; w++) {
                
                if (wt[i] <= w) {
                    t[i][w] = max (
                            t[i+1][w - wt[i]] + val[i], //take
                            t[i+1][w]                  // skip
                            );
                } else {
                    t[i][w] = t[i+1][w];
                }
            }
        }
        
        return t[0][W];
    }
```
### Subset sum
> Given an array of positive integers arr[] and a value sum, determine if there is a subset of arr[] with sum equal to given sum. 

```bash
Examples:

Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 9
Output: true 
Explanation: Here there exists a subset with target sum = 9, 4+3+2 = 9.

Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 30
Output: false
Explanation: There is no subset with target sum 30.

Input: arr[] = [1, 2, 3], sum = 6
Output: true
Explanation: The entire array can be taken as a subset, giving 1 + 2 + 3 = 6.
```
Recursion
```cpp
class Solution {
  public:
    bool isSubsetSum(vector<int>& arr, int sum) {
        // code here
        int i = 0;
        return rr(arr, sum, i);
        
    }
    
    bool rr(vector<int>& arr, int sum, int i) {
        // Base cases
        if (sum == 0)
            return true;

        if (i == arr.size())
            return false;
            
        if (arr[i] >= sum) {
            return rr(arr, sum - arr[i], i + 1) || rr(arr, sum, i + 1);
        } else {
            return rr(arr, sum, i + 1);
        }
    }
};
```

DP
```cpp
class Solution {
  public:
    bool isSubsetSum(vector<int>& arr, int sum) {
        // code here
        vector<vector<int>> t(arr.size() + 1, vector<int>(sum + 1, -1));
        
        return rr(arr, sum, 0, t);
    }
    
    bool rr(vector<int>& arr, int sum, int i, vector<vector<int>> &t) {
        if (sum == 0)
            return true;
        
        if (i == arr.size())
            return false;
        
        if (t[i][sum] != -1)
            return t[i][sum];
        
        if (arr[i] <= sum) {
            t[i][sum] =
                rr(arr, sum - arr[i], i + 1, t) ||   // take
                rr(arr, sum, i + 1, t);              // not take
        } else {
            t[i][sum] = rr(arr, sum, i + 1, t);
        }

        return t[i][sum];
    }
};
```

### Equal sum partition
> Given an array arr[], determine if it can be partitioned into two subsets such that the sum of elements in both parts is the same.

Note: Each element must be in exactly one subset.

```bash
Examples:

Input: arr = [1, 5, 11, 5]
Output: true
Explanation: The two parts are [1, 5, 5] and [11].

Input: arr = [1, 3, 5]
Output: false
Explanation: This array can never be partitioned into two such parts.
```
Apporach:
    - Some similarity with subset sum
    - to be equally divisibile total sum has to be even
    - If sum is even i can search for sm/2 in the array and if found (usbing subset sum) we can partition it

```cpp
class Solution {
  public:
    bool equalPartition(vector<int>& arr) {
        
        int sm = 0;
        for(auto n: arr)
            sm+= n;
        
        if ((sm % 2) == 0)
            return isSubsetSum(arr, sm/2);
        
        return false;
    }
};
```

### Perfect Sum Problem

> Given an array arr of non-negative integers and an integer target, the task is to count all subsets of the array whose sum is equal to the given target

```bash
Examples:

Input: arr[] = [5, 2, 3, 10, 6, 8], target = 10
Output: 3
Explanation: The subsets {5, 2, 3}, {2, 8}, and {10} sum up to the target 10.

Input: arr[] = [2, 5, 1, 4, 3], target = 10
Output: 3
Explanation: The subsets {2, 1, 4, 3}, {5, 1, 4}, and {2, 5, 3} sum up to the target 10.

Input: arr[] = [5, 7, 8], target = 3
Output: 0
Explanation: There are no subsets of the array that sum up to the target 3.

Input: arr[] = [35, 2, 8, 22], target = 0
Output: 1
Explanation: The empty subset is the only subset with a sum of 0.

Recursion

```cpp
class Solution {
  public:
    int perfectSum(vector<int>& arr, int target) {
        // code here
        int i = 0;
        return rr(arr, target, i);
    }
    
    int rr(vector<int>& arr, int sum, int i) {
        // base condition
        if (i == arr.size()) {
            return (sum == 0) ? 1 : 0;
        }
        
        int exclude =  rr(arr, sum, i + 1);
        
        int include = 0;
        if (arr[i] <= sum) {
            include = rr(arr, sum - arr[i], i + 1);
        }
        
        return exclude + include;
    }
};
```

### Min subset sum diff
> Given an array arr[]  containing non-negative integers, the task is to divide it into two sets set1 and set2 such that the absolute difference between their sums is minimum and find the minimum difference.

```bash
Examples:

Input: arr[] = [1, 6, 11, 5]
Output: 1
Explanation: 
Subset1 = {1, 5, 6}, sum of Subset1 = 12 
Subset2 = {11}, sum of Subset2 = 11 
Hence, minimum difference is 1.

Input: arr[] = [1, 4]
Output: 3
Explanation: 
Subset1 = {1}, sum of Subset1 = 1
Subset2 = {4}, sum of Subset2 = 4
Hence, minimum difference is 3.

Input: arr[] = [1]
Output: 1
Explanation: 
Subset1 = {1}, sum of Subset1 = 1
Subset2 = {}, sum of Subset2 = 0
Hence, minimum difference is 1.
```

```cpp
```
### Count the number of subset with a given difference

### Target Sum