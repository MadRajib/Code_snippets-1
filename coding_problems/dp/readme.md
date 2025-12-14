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
    - Subset sum
    - Equal sum partition
    - count of subset sum
    - min subset sum diff
    - target sum
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
