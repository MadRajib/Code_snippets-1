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
1. [Unbounded Knapsack problem](#unbounded-knapsack-problems)
    - [Rod Cutting](#rod-cutting)
    - [Coin Change I](#coin-change-i)
    - [Coin Change II](#coin-change-ii)
    - [Maximum Ribbon Cut](#maximum-ribbon-cut)
1. [Longest Common Subsequence](#longest-common-subsequence)
    - [Longest Common SubString](#longest-common-substring)
    - [Print longest common subsequence](#print-longest-common-subsequence)
    - [Shortest Common Supersequence](#shortest-common-supersequence)
    - [Print shortest common Supersequence](#print-shortest-common-supersequence)
    - [Minimum Number of Insertion and Deletion to convert String a to String b](#minimum-number-of-insertion-and-deletion-to-convert-string-a-to-string-b)
    - [Longest Palindromic Subsequence](#longest-palindromic-subsequence)
    - [Minimum number of deletion in a string to make it a palindrome](#minimum-number-of-deletion-in-a-string-to-make-it-a-palindrome)
    - [Longest repeating subsequence](#longest-repeating-subsequence)
    - [Sequence Pattern Matching](#sequence-pattern-matching)
    - [Minimum number of insertion in a string to make it a palindrome](#minimum-number-of-insertion-in-a-string-to-make-it-a-palindrome)
1. [Matrix chain multiplication](#matrix-chain-multiplication)
    - [Palindrome Partitioning Recursive](#palindrome-partitioning-recursive)
    - [Word Break](#word-break)
    - [Integer Break](#integer-break)
1. [Climbing Stairs](#climbing-stairs)
1. [House Robber II](#house-robber-ii)
1. [Decode Ways](#decode-ways)
1. [Unique Paths](#unique-paths)
1. [Perfect Squares](#perfect-squares)
1. [Unique Paths II](#unique-paths-ii)
1. [Minimum Path Sum](#minimum-path-sum)
1. [Last Stone Weight II](#last-stone-weight-ii)
1. [Edit Distance](#edit-distance)
1. [Best Time to Buy and Sell Stock with Cooldown](#best-time-to-buy-and-sell-stock-with-cooldown)


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

Bottom Up
```cpp
class Solution {
  public:
    bool isSubsetSum(vector<int>& arr, int sum) {
        // code here
        vector<vector<int>> t(arr.size() + 1, vector<int>(sum + 1, 0));
        
        // base condition
        // sum == 0 -> true
        // i == n -> false // ie with no elements
        for (int j = 0; j <= sum; j++)
            t[arr.size()][j] = false;
        
        for (int i = 0; i <= arr.size(); i++)
            t[i][0] = true;
        
        for (int i = arr.size() -1; i >=0 ; i--) {
            for (int sm = 0; sm <= sum; sm++) {
                if (arr[i] <= sm) {
                    t[i][sm] =
                        t[i + 1][sm - arr[i]] ||   // take
                        t[i + 1][sm];              // not take
                } else {
                    t[i][sm] = t[i + 1][sm];
                }
            }
        }
        
        
        return t[0][sum];
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
```

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

Apporach:
- we need to find two sets s1 and s2 whose sums differennce is min
- i.e s1 - s2 -> min
- i.e total_sum - s2 - s2 -> min
- i.e total_sum - 2*s2 -> min
- find s2 from 0 to total_sum or total_sum and save the min
- in bottom up tabulation each [0][n] tells if with all the elements sum 'n' is possible or not
- so we can create dp table for target sum -> total_sum, then iterate over d[0]0-> sm/2]
- and calculate total_sum - 2*s2 and save the min.

```cpp
class Solution {
    private:
    
  public:
    int minDifference(vector<int>& arr) {
        // Your code goes here
        
        int sum = 0;
        for (auto c: arr)
            sum +=c;
        
        // code here
        vector<vector<int>> t(arr.size() + 1, vector<int>(sum + 1, 0));
        
        // base condition
        // sum == 0 -> true
        // i == n -> false // ie with no elements
        for (int j = 0; j <= sum; j++)
            t[arr.size()][j] = false;
        
        for (int i = 0; i <= arr.size(); i++)
            t[i][0] = true;
        
        for (int i = arr.size() -1; i >=0 ; i--) {
            for (int sm = 0; sm <= sum; sm++) {
                if (arr[i] <= sm) {
                    t[i][sm] =
                        t[i + 1][sm - arr[i]] ||   // take
                        t[i + 1][sm];              // not take
                } else {
                    t[i][sm] = t[i + 1][sm];
                }
            }
        }
        
        
        int min_diff = INT_MAX;
        for (int i = 0; i <= sum/2; i++){
            if (t[0][i])
                min_diff = min(min_diff, sum - 2*i);
        }
        
        return min_diff;
    }
};
```
### Count the number of subset with a given difference
Apporach:
- s1 - s2 = diff
- range - s2 - s2 = diff
- s2 = (diff + range) / 2
- Find no of subsets having sum s2; ie perfect sum problem

### Target Sum
> You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target

```bash
Example 1:

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:

Input: nums = [1], target = 1
Output: 1
```
Apporach:
- Same as pervious problem, count no of subset sum difference 3.
- -1 + 1 + + 1+ 1 + 1 -> (1 + 1 + 1 +1) - (1) = 3 ? similar ? 

### Unbounded Knapsack Problems

```cpp
// decision tree
        if (wt[i] <= w) {
            // take the weight or skip the weight
            // return max (   rr(wt, val, i + 1, w - wt[i]) + val[i],
            return max (   rr(wt, val, i, w - wt[i]) + val[i], // if take then i can be taken again
                    rr(wt, val, i + 1, w));
        } else {
            // check the next weight
            return rr(wt, val, i + 1, w);
        }
```

### Rod Cutting
> Given a rod of length n inches and an array price[], where price[i] denotes the value of a piece of length i. Your task is to determine the maximum value obtainable by cutting up the rod and selling the pieces.

Note: n = size of price, and price[] is 1-indexed array.

```bash
Example:

Input: price[] = [1, 5, 8, 9, 10, 17, 17, 20]
Output: 22
Explanation: The maximum obtainable value is 22 by cutting in two pieces of lengths 2 and 6, i.e., 5 + 17 = 22.

Input: price[] = [3, 5, 8, 9, 10, 17, 17, 20]
Output: 24
Explanation: The maximum obtainable value is 24 by cutting the rod into 8 pieces of length 1, i.e, 8*price[1] = 8*3 = 24.

Input: price[] = [3]
Output: 3
Explanation: There is only 1 way to pick a piece of length 1.
```

Apporach:
- Doesn't sounds similar to 0/1 knapsack problem
- total weight =  len of rod
- price of each length give
- items -> each length size is item. L1 L2 L3 L4...

Recursion
```cpp
int cutRod(vector<int> &price) { 
    int total_len = price.size();
    return rr(1, total_len, price);
}

int rr(int i, int L, vector<int> &price) {
    // base, len becomes 0
    if (L == 0 || i > price.size())
        return 0;
    
    if (i <= L) {
        return max(rr(i, L - i, price) + price[i-1],
                    rr(i + 1, L, price));
    }
    
    return rr(i + 1, L, price);
}
```

Memolisation

```cpp
class Solution {
  public:
    int cutRod(vector<int> &price) {
        
        int W = price.size();
        vector<int> wt(price.size(), 0);
        for (int i = 0; i < price.size(); i++)
            wt[i] = i + 1;
        
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
                            t[i][w - wt[i]] + price[i], //take
                            t[i+1][w]                  // skip
                            );
                } else {
                    t[i][w] = t[i+1][w];
                }
            }
        }
        
        return t[0][W];

    }
};
```
### Coin Change I
> Given an integer array coins[ ] representing different denominations of currency and an integer sum, find the number of ways you can make sum by using different combinations from coins[ ]. 
Note: Assume that you have an infinite supply of each type of coin. Therefore, you can use any coin as many times as you want.
Answers are guaranteed to fit into a 32-bit integer. 

```bash
Examples:

Input: coins[] = [1, 2, 3], sum = 4
Output: 4
Explanation: Four Possible ways are: [1, 1, 1, 1], [1, 1, 2], [2, 2], [1, 3].

Input: coins[] = [2, 5, 3, 6], sum = 10
Output: 5
Explanation: Five Possible ways are: [2, 2, 2, 2, 2], [2, 2, 3, 3], [2, 2, 6], [2, 3, 5] and [5, 5].

Input: coins[] = [5, 10], sum = 3
Output: 0
Explanation: Since all coin denominations are greater than sum, no combination can make the target sum.
```

Apporach:
- Same as subset sum problem

Recursion:
```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int tmp = rr(0, amount, coins);
        return (tmp == INT_MAX)? -1 : tmp;
    }

    int rr(int i, int C, vector<int>& coins) {
        if (!C)
            return 0;
        
        if (i >= coins.size() || C < 0)
            return INT_MAX;

        int res = rr(i + 1, C, coins);

        if (coins[i] <= C) {
            int tmp = rr(i, C - coins[i], coins);
            // INT_MAX + 1 can over flow
            if (tmp != INT_MAX)
                res = min(res, 1 + tmp);
        }

        return res;
    }
};
```

```cpp
class Solution {
  public:
    int count(vector<int>& coins, int amount) {
        // code here.
        vector<vector<int>> t(coins.size() + 1, vector<int>(amount + 1, 0));

        // base condtion
        // coin(i) = 0 -> 1 way {}
        // amount(j) = 0 -> 0 way {}
        for (int i = 0; i <= coins.size(); i++)
            t[i][0] = 1;
    
        for (int j =0; j <= amount; j++)
            t[coins.size()][j] = 0;
        
        // with no coins amount 0 is possible
        t[coins.size()][0] = 1;

        for (int i = coins.size()-1; i >=0; i--) {
            for (int j = 0; j <= amount; j++) {
                if (coins[i] <= j) {
                    t[i][j] = t[i][j - coins[i]] + t[i+1][j];
                } else {
                    t[i][j] = t[i+1][j];
                }
            }
        }

        return t[0][amount];
    }
};
```
### Coin Change II
> You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

```bash
Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3
Output: -1

Example 3:

Input: coins = [1], amount = 0
Output: 0
```

Approach:
- Intialize when coins == 0 then entifinite no of coins required.
- min(t[i][j - coins[i]] + 1 , t[i+1][j]);

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> t(coins.size() + 1, vector<int>(amount + 1, 0));

        // base condtion
        // coin(i) = 0 -> 1 way {}
        // amount(j) = 0 -> INT_MAX infinite coins
        for (int i = 0; i <= coins.size(); i++)
            t[i][0] = 0;
    
        for (int j =0; j <= amount; j++)
            t[coins.size()][j] = INT_MAX - 1;
        
        t[coins.size()][0] = 0;

        for (int i = coins.size()-1; i >=0; i--) {
            for (int j = 0; j <= amount; j++) {
                if (coins[i] <= j) {
                    t[i][j] = min(t[i][j - coins[i]] + 1 , t[i+1][j]);
                } else {
                    t[i][j] = t[i+1][j];
                }
            }
        }

        return t[0][amount] != INT_MAX -1 ? t[0][amount]: -1 ;
    }
};
```
### Maximum Ribbon Cut

### Longest Common Subsequence
> Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

```bash
For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.


Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
```

Apporach:
- base condition if any string is null return 0
- if matches 1 + LCS(i++, j++)
- else if then check if first string matches with second reduced string or second string matches with first reduce string
- return the max from the both.

Recursion Apporach:

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        return LCS(text1, text2, 0, 0);
    }

    int LCS(string& text1, string& text2, int i, int j) {
        
        // base condition
        if (i == text1.length() || j == text2.length())
            return 0;
        
        if (text1[i] ==  text2[j])
            return 1 + LCS(text1, text2, i + 1, j + 1);
        else 
            return max(
                LCS(text1, text2, i, j + 1),
                LCS(text1, text2, i + 1, j));
    }
};
```

Bottom Up

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> t(text1.length() + 1 , vector<int>(text2.length() +1 , 0));

        // base
        // i = text1.length() = 0
        // j = text2.lentth() = 0

        for (int i = 0; i <= text1.length(); i++)
            t[i][text2.length()] = 0;

        for (int j = 0; j <= text2.length(); j++)
            t[text1.length()][j] = 0;
        
        for (int i = text1.length() -1; i >= 0; i--) {
            for (int j = text2.length() -1 ; j >= 0; j--) {
                if (text1[i] ==  text2[j])
                    t[i][j] = 1 + t[i + 1][j + 1];
                else 
                    t[i][j] = max(t[i][j+1], t[i+1][j]);
            }
        }

        return t[0][0];
    }
};
```

### Longest Common Substring
> You are given two strings s1 and s2. Your task is to find the length of the longest common substring among the given strings.

```bash
Examples:
Input: s1 = "ABCDGH", s2 = "ACDGHR"
Output: 4
Explanation: The longest common substring is "CDGH" with a length of 4.

Input: s1 = "abc", s2 = "acb"
Output: 1
Explanation: The longest common substrings are "a", "b", "c" all having length 1.

Input: s1 = "YZ", s2 = "yz"
Output: 0
```
Approach:
- Same as LCS with slight variation
- when mistach occurs we save 0 for t[i][j]
- for each match we store the max length
- at the end return the max value

```cpp
class Solution {
  public:
    int longestCommonSubstr(string& text1, string& text2) {
        // your code here
        vector<vector<int>> t(text1.length() + 1 , vector<int>(text2.length() +1 , 0));

        // base
        // i = text1.length() = 0
        // j = text2.lentth() = 0

        for (int i = 0; i <= text1.length(); i++)
            t[i][text2.length()] = 0;

        for (int j = 0; j <= text2.length(); j++)
            t[text1.length()][j] = 0;
        
        int res = 0;
        for (int i = text1.length() -1; i >= 0; i--) {
            for (int j = text2.length() -1 ; j >= 0; j--) {
                if (text1[i] ==  text2[j]) {
                    t[i][j] = 1 + t[i + 1][j + 1];
                    res = max(res, t[i][j]);
                }
                else 
                    t[i][j] = 0;
            }
        }
        
        return res;
        
    }
};
```

### Print Longest common subsequence
Apporach
- build LCS table
- start from i = 0 and j = 0; until i != n && j != m
    - if s1[i] == s2[j] i++, j++, store char
    else if t[i+1][j] > t[i][j+1], i = i++;
    else j++; 

### Shortest Common Supersequence
> Given two strings s1 and s2, find the length of the smallest string which has both s1 and s2 as its sub-sequences.
Note: s1 and s2 can have both uppercase and lowercase English letters.

```bash
Examples:

Input: s1 = "geek", s2 = "eke"
Output: 5
Explanation: String "geeke" has both string "geek" and "eke" as subsequences.

Input: s1 = "AGGTAB", s2 = "GXTXAYB"
Output: 9
Explanation: String "AGXGTXAYB" has both string "AGGTAB" and "GXTXAYB" as subsequences.

Input: s1 = "geek", s2 = "ek"
Output: 4
Explanation: String "geek" has both string "geek" and "ek" as subsequences.
```

Apporach:
    - text1.len + text2.len - lcs

```cpp
class Solution {
  public:
    int minSuperSeq(string &text1, string &text2) {
        // code here
         vector<vector<int>> t(text1.length() + 1 , vector<int>(text2.length() +1 , 0));

        // base
        // i = text1.length() = 0
        // j = text2.lentth() = 0

        for (int i = 0; i <= text1.length(); i++)
            t[i][text2.length()] = 0;

        for (int j = 0; j <= text2.length(); j++)
            t[text1.length()][j] = 0;
        
        for (int i = text1.length() -1; i >= 0; i--) {
            for (int j = text2.length() -1 ; j >= 0; j--) {
                if (text1[i] ==  text2[j])
                    t[i][j] = 1 + t[i + 1][j + 1];
                else 
                    t[i][j] = max(t[i][j+1], t[i+1][j]);
            }
        }

        return text1.length() + text2.length() - t[0][0];
    }
};
```

### Print shortest common Supersequence

Approach:
- build LCS table
- start from i = 0 and j = 0; until i < n && j < m
    - if s1[i] == s2[j] i++, j++, store char
    - else if t[i+1][j] > t[i][j+1], store text1[i] i = i++; 
    - else store text2[j] j++; 

```cpp
class Solution {
public:
    string shortestCommonSupersequence(string text1, string text2) {
        string res = "";
        vector<vector<int>> t(text1.length() + 1 , vector<int>(text2.length() +1 , 0));

        // base
        // i = text1.length() = 0
        // j = text2.lentth() = 0

        for (int i = 0; i <= text1.length(); i++)
            t[i][text2.length()] = 0;

        for (int j = 0; j <= text2.length(); j++)
            t[text1.length()][j] = 0;
        
        for (int i = text1.length() -1; i >= 0; i--) {
            for (int j = text2.length() -1 ; j >= 0; j--) {
                if (text1[i] ==  text2[j])
                    t[i][j] = 1 + t[i + 1][j + 1];
                else 
                    t[i][j] = max(t[i][j+1], t[i+1][j]);
            }
        }

        int i = 0;
        int j = 0;

        while (i < text1.length() && j < text2.length()) {
            if (text1[i] == text2[j]) {
                res += text1[i];
                i++;
                j++;
            } else if (t[i+1][j] > t[i][j+1]) {
                res += text1[i];
                i++;
            } else {
                res += text2[j];
                j++;
            }
        }

        while (i < text1.length()) {
            res += text1[i++];
        }

        while (j < text2.length()) {
            res += text2[j++];
        }

        return res;
    }
};
```

### Minimum Number of Insertion and Deletion to convert String a to String b

Apporach:
- find LCS
- deletion = text1.len - LCS
- inserstion = text2.len - LCS

- result = insertion + deletion;

```cpp
class Solution {

  public:
    int minOperations(string &text1, string &text2) {
        // Your code goes here
         vector<vector<int>> t(text1.length() + 1 , vector<int>(text2.length() +1 , 0));

        // base
        // i = text1.length() = 0
        // j = text2.lentth() = 0

        for (int i = 0; i <= text1.length(); i++)
            t[i][text2.length()] = 0;

        for (int j = 0; j <= text2.length(); j++)
            t[text1.length()][j] = 0;
        
        for (int i = text1.length() -1; i >= 0; i--) {
            for (int j = text2.length() -1 ; j >= 0; j--) {
                if (text1[i] ==  text2[j])
                    t[i][j] = 1 + t[i + 1][j + 1];
                else 
                    t[i][j] = max(t[i][j+1], t[i+1][j]);
            }
        }
        
        int deletion  = text1.length() - t[0][0];
        int insertion = text2.length() - t[0][0];
        
        return deletion + insertion;
    }
};
```

###  Longest Palindromic Subsequence

Approach:
    - LPS(a) -> LCS(a, reverse(a))

### Minimum number of deletion in a string to make it a palindrome

Apporach:
- Min no deletion = text.len - LPS = text.len - LCS(a, reverse(a))

### Longest repeating subsequence

Apporach:
- LCS variants on same string, just dont check same index
- if the subsequence is reapting in string a large part will be common in LCS(s, s)

```cpp
        for (int i = text1.length() -1; i >= 0; i--) {
            for (int j = text2.length() -1 ; j >= 0; j--) {
                if (text1[i] ==  text2[j] && (i != j) )     // dont match with same index
                    t[i][j] = 1 + t[i + 1][j + 1];
                else 
                    t[i][j] = max(t[i][j+1], t[i+1][j]);
            }
        }

        return t[0][0];
```

### Sequence Pattern Matching
Given two string s and t, return true if s is a subsequence of t, or false otherwise.

Apporach
-  LCS(pattern, target) == pattern.len


### Minimum number of insertion in a string to make it a palindrome
> Same as deltetion [Minimum number of deletion in a string to make it a palindrome](#minimum-number-of-deletion-in-a-string-to-make-it-a-palindrome)

### Matrix chain multiplication
> Given an array arr[] which represents the dimensions of a sequence of matrices where the ith matrix has the dimensions (arr[i-1] x arr[i]) for i>=1, find the most efficient way to multiply these matrices together. The efficient way is the one that involves the least number of multiplications.

```bash
Input: arr[] = [2, 1, 3, 4]
Output: 20
Explanation: There are 3 matrices of dimensions 2 × 1, 1 × 3, and 3 × 4, Let this 3 input matrices be M1, M2, and M3. There are two ways to multiply: ((M1 x M2) x M3) and (M1 x (M2 x M3)), note that the result of (M1 x M2) is a 2 x 3 matrix and result of (M2 x M3) is a 1 x 4 matrix. 
((M1 x M2) x M3)  requires (2 x 1 x 3) + (2 x 3 x 4) = 30 
(M1 x (M2 x M3))  requires (1 x 3 x 4) + (2 x 1 x 4) = 20. 
The minimum of these two is 20.

Input: arr[] = [1, 2, 3, 4, 3]
Output: 30
Explanation: There are 4 matrices of dimensions 1 × 2, 2 × 3, 3 × 4, 4 × 3. Let this 4 input matrices be M1, M2, M3 and M4. The minimum number of multiplications are obtained by ((M1 x M2) x M3) x M4). The minimum number is (1 x 2 x 3) + (1 x 3 x 4) + (1 x 4 x 3) = 30.

Input: arr[] = [3, 4]
Output: 0
Explanation: As there is only one matrix so, there is no cost of multiplication.
```

Apporach:
1. Find i & j
1. Find the base condition
1. loop from k to have two partitions
1. from temporary ans build the actual ans

```cpp
class Solution {
  public:
    int matrixMultiplication(vector<int> &arr) {
        // code here
        return solve(arr, 1, arr.size() - 1);
    }
    
    int solve(vector<int>& arr, int i, int j) {
        if (i >= j)
            return 0;
        
        int res = INT_MAX;
        for (int k = i; k < j; k++) {
            int ans = solve(arr, i, k) + solve(arr, k + 1, j);
            
            ans += arr[i - 1] * arr[k] * arr[j];
            
            res = min(res, ans);
        }
        
        return res;
    }
};
```

Memolisation
```cpp
class Solution {
  public:
    int matrixMultiplication(vector<int> &arr) {
        // code here
        vector<vector<int>> t(arr.size(), vector<int>(arr.size(), -1));
        return solve(arr, 1, arr.size() - 1, t);
    }
    
    int solve(vector<int>& arr, int i, int j, vector<vector<int>> &t) {
        if (i >= j)
            return 0;
            
        if(t[i][j]!=-1)
            return t[i][j];
        
        int res = INT_MAX;
        for (int k = i; k < j; k++) {
            
            int ans = solve(arr, i, k, t)
                    + solve(arr, k + 1, j, t);
            
            ans += arr[i - 1] * arr[k] * arr[j];
            
            res = min(res, ans);
        }
        
        t[i][j] = res;
        
        return res;
    }
};
```

### Palindrome Partitioning Recursive
> Given a string s, a partitioning of the string is a palindrome partitioning if every sub-string of the partition is a palindrome. Determine the fewest cuts needed for palindrome partitioning of the given string.

```bash
Examples:

Input: s = "geek" 
Output: 2 

Explanation: We need to make minimum 2 cuts, i.e., "g | ee | k".
Input: s = "aaaa" 
Output: 0
Explanation: The string is already a palindrome.

Input: s = "ababbbabbababa" 
Output: 3
Explanation: We need to make minimum 3 cuts, i.e., "aba | bb | babbab | aba".

```

Apporach:
- if a string is already palindrome we don need any partition
- for a cut say at k, if first part is not a palindrome then this cut is not valid, we jump to next pos
- our goal is to min cut the string to make all the group as palindrome
- if first half is palindrome then check the next half. 
Recursive
```cpp
class Solution {
    private:
    bool check_palindrome(string s, int i, int j) {
        while( i <= j) {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }

        return true;
    }
public:
    int minCut(string s) {
        return solve(s, 0, s.length() - 1);
    }

    int solve(string& s, int i, int j) {
        if (i >= j)
            return 0;
        
        if (check_palindrome(s, i, j))
            return 0;

        int res = INT_MAX;
        for (int k = i; k < j; k++) {
            if (!check_palindrome(s, i, j))
                continue ;
            int temp = solve(s, k+1, j) + 1;
            res =  min(res, temp);
        }

        return res;
    }
};
```

Memorisation
```cpp
class Solution {
  private:
    bool check_palindrome(string s, int i, int j) {
        while( i <= j) {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }

        return true;
    }
public:
    int palPartition(string s) {
        vector<vector<int>> t(s.length(), vector<int>(s.length(), -1));
        return solve(s, 0, s.length() - 1, t);
    }

    int solve(string& s, int i, int j, vector<vector<int>>&  t) {
        if (i >= j)
            return 0;
        
        if (t[i][j] != -1)
            return t[i][j];
        
        if (check_palindrome(s, i, j))
            return 0;
        
        
        int res = INT_MAX;
        for (int k = i; k < j; k++) {
            if (!check_palindrome(s, i, k))
                continue ;
                
            int l = t[k + 1][j] != -1 ? t[k +1][j]: solve(s, k+1, j, t);
            int temp = l + 1;
            res =  min(res, temp);
        }

        t[i][j] = res;
        return res;
    }
};
```

### Word Break
> Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of dictionary words.

You are allowed to reuse words in the dictionary an unlimited number of times. You may assume all dictionary words are unique.

```bash
Example 1:

Input: s = "neetcode", wordDict = ["neet","code"]

Output: true
Explanation: Return true because "neetcode" can be split into "neet" and "code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen","ape"]

Output: true
Explanation: Return true because "applepenapple" can be split into "apple", "pen" and "apple". Notice that we can reuse words and also not use all the words.

Example 3:

Input: s = "catsincars", wordDict = ["cats","cat","sin","in","car"]

Output: false
```

Recursion
```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> mp(wordDict.begin(), wordDict.end());
        return rr(s, mp, 0);
    }

    bool rr(const string& s, const unordered_set<string>& mp, int i) {
        if (i == s.size()) {
            return true;
        }

        for (int j = i; j < s.size(); j++) {
            // if first part is present than only check other part
            if (mp.find(s.substr(i, j - i + 1)) != mp.end()) {
                if (rr(s, mp, j + 1)) {
                    return true;
                }
            }
        }
        return false;

        // this is also correct 
        //
        // bool res = false;
        // for (int j = i; j < s.size(); j++) {
        //     // if first part is present than only check other part
        //     if (mp.find(s.substr(i, j - i + 1)) != mp.end()) {
        //         res = res || rr(s, mp, j + 1);
        //     }
        // }
        // return res;
    }
};
```

### Integer Break
> You are given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.

Return the maximum product you can get.

```bash
Example 1:

Input: n = 4

Output: 4
Explanation: 4 = 2 + 2, 2 x 2 = 4.

Example 2:

Input: n = 12

Output: 81
Explanation: 12 = 3 + 3 + 3 + 3, 3 x 3 x 3 x 3 = 81.
```

Recursion:
```cpp
class Solution {
public:
    int integerBreak(int n) {
        return dfs(n, n);
    }

private:
    int dfs(int num, int original) {
        if (num == 1) return 1;

        int res = (num == original) ? 0 : num;
        for (int i = 1; i < num; i++) {
            // break in two parts left will be i and right will num -i
            int val = dfs(i, original) * dfs(num - i, original);
            res = max(res, val);
        }
        return res;
    }
};
```

### Climbing Stairs
> You are given an integer n representing the number of steps to reach the top of a staircase. You can climb with either 1 or 2 steps at a time.

Return the number of distinct ways to climb to the top of the staircase.

```bash
Example 1:

Input: n = 2

Output: 2
Explanation:

1 + 1 = 2
2 = 2
Example 2:

Input: n = 3

Output: 3
Explanation:

1 + 1 + 1 = 3
1 + 2 = 3
2 + 1 = 3
```

Recursion
```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (!n) return 0;
        if (n == 1) return 1;
        if (n == 2) return 2;

        return climbStairs(n-2) + climbStairs(n-1);
    }
};
```

Bottom Up
```cpp
class Solution {
public:
    unordered_map<int, int> dp;
    int climbStairs(int n) {
        vector<int> tb(n + 1, 0);
        tb[0] = 0;
        tb[1] = 1;
        tb[2] = 2;

        for (int i = 3; i <= n; i++) {
            tb[i] = tb[i - 1] + tb[i - 2];
        }

        return tb[n];
    }
};
```

### House Robber
> You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are arranged in a straight line, i.e. the ith house is the neighbor of the (i-1)th and (i+1)th house.

You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system will automatically alert the police if two adjacent houses were both broken into.

Return the maximum amount of money you can rob without alerting the police.

```bash

Example 1:

Input: nums = [1,1,3,3]

Output: 4
Explanation: nums[0] + nums[2] = 1 + 3 = 4.

Example 2:

Input: nums = [2,9,8,3,6]

Output: 16
Explanation: nums[0] + nums[2] + nums[4] = 2 + 8 + 6 = 16.
```

Recursion
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        return rr(nums, 0);
    }

    int rr(vector<int>& nums, int i) {
        if (i >= nums.size())
            return 0;
        
        return max(rr(nums, i+2) + nums[i], rr(nums, i+1));
    }
};

```

Memolisation
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> t(nums.size(), -1);
        return rr(nums, 0, t);
    }

    int rr(vector<int>& nums, int i, vector<int> &t) {
        if (i >= nums.size())
            return 0;
        
        if (t[i] != -1)
            return t[i];
        
        t[i] = max(rr(nums, i+2, t) + nums[i], rr(nums, i+1, t));

        return t[i];
    }
};

```

Bottom up

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> tb(nums.size() + 1, 0);
        tb[nums.size()] = 0; // when no element
        tb[nums.size() - 1] = nums[nums.size() - 1]; // when only one element

        for (int i = nums.size() - 2; i >= 0 ; i--) {
            tb[i] = max(
                tb[i + 2] + nums[i],
                tb[i + 1]);
        }

        return tb[0];
    } 
};

```

### House Robber II
> You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are arranged in a circle, i.e. the first house and the last house are neighbors.

You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system will automatically alert the police if two adjacent houses were both broken into.

Return the maximum amount of money you can rob without alerting the police.

```bash
Example 1:

Input: nums = [3,4,3]

Output: 4
Explanation: You cannot rob nums[0] + nums[2] = 6 because nums[0] and nums[2] are adjacent houses. The maximum you can rob is nums[1] = 4.

Example 2:

Input: nums = [2,9,8,3,6]

Output: 15
Explanation: You cannot rob nums[0] + nums[2] + nums[4] = 16 because nums[0] and nums[4] are adjacent houses. The maximum you can rob is nums[1] + nums[4] = 15.
```

Apporach:
- find max from 0 to end -1;
- find max from 1 to end
- return the max.
- since if we rob first we cannot rob the last and vise versa

```cpp
class Solution {
    int rr(vector<int>& nums, int i, int e, vector<int> &t) {
        if (i > e)
            return 0;
        
        if (t[i] != -1)
            return t[i];
        
        t[i] = max(rr(nums, i+2, e, t) + nums[i], rr(nums, i+1, e, t));

        return t[i];
    }
public:
    int rob(vector<int>& nums) {
        
        if (nums.size() == 1) return nums[0];

        vector<int> t(nums.size(), -1);
        int _r2 = rr(nums, 1, nums.size() - 1, t);
        
        fill(t.begin(), t.end(), -1);
        int _r1 = rr(nums, 0, nums.size() - 2, t);

        return max(_r1, _r2);
    }
};

```
Bottom Up
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
         if (nums.size() == 1) return nums[0];

        vector<int> tb(nums.size() + 1, 0);
        
        // first we will go from house 1st to n - 1 i.e skipping the last
        tb[nums.size()] = 0; // when no element
        tb[nums.size() - 1] = nums[nums.size() - 1]; // when only one element

        for (int i = nums.size() - 2; i >= 1 ; i--) {
            tb[i] = max(
                tb[i + 2] + nums[i],
                tb[i + 1]);
        }

        int temp = tb[1];
        fill(tb.begin(), tb.end(), 0);

         // second we will go from house 2st to nth i.e skipping the first
        tb[nums.size() - 1] = 0; 
        tb[nums.size() - 2] = nums[nums.size() - 2];

        for (int i = nums.size() - 3; i >= 0 ; i--) {
            tb[i] = max(
                tb[i + 2] + nums[i],
                tb[i + 1]);
        }

        // finding the max of both
        return max(tb[0], temp);
    }
};

```


### Decode Ways
> A string consisting of uppercase english characters can be encoded to a number using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode a message, digits must be grouped and then mapped back into letters using the reverse of the mapping above. There may be multiple ways to decode a message. For example, "1012" can be mapped into:

"JAB" with the grouping (10 1 2)
"JL" with the grouping (10 12)
The grouping (1 01 2) is invalid because 01 cannot be mapped into a letter since it contains a leading zero.

Given a string s containing only digits, return the number of ways to decode it. You can assume that the answer fits in a 32-bit integer.

```bash
Example 1:

Input: s = "12"

Output: 2

Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: s = "01"

Output: 0
Explanation: "01" cannot be decoded because "01" cannot be mapped into a letter.
```

Recusion
```cpp
class Solution {
public:
    int numDecodings(string s) {
        return rr(s, 0);
    }

    int rr(string& s, int i) {
        if (i == s.length())
            return 1;
        if (s[i] == '0')
            return 0;
         
        int temp = rr(s, i + 1) ;

        if (i < s.length() - 1) {
            if (s[i] == '1' || (s[i] == '2' && s[i] < '7'))
                temp += rr(s, i + 2) ;
        }

        return temp;
    }
};

```

### Unique Paths
> There is an m x n grid where you are allowed to move either down or to the right at any point in time.

Given the two integers m and n, return the number of possible unique paths that can be taken from the top-left corner of the grid (grid[0][0]) to the bottom-right corner (grid[m - 1][n - 1]).

You may assume the output will fit in a 32-bit integer.

```bash
Example 1:
Input: m = 3, n = 6

Output: 21
Example 2:

Input: m = 3, n = 3

Output: 6
```

Recursion
```cpp
class Solution {
    int M, N;
public:
    int uniquePaths(int m, int n) {
        M = m;
        N = n;
        return rr(0, 0);
    }

    int rr(int i, int j) {
        if (i >= M || j >= N)
            return 0;
        
        if (i == M - 1 && j == N -1 )
            return 1;
        
        return rr(i, j+1) + rr(i+1, j);
    }
};

```

### Perfect Squares
> You are given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer. For example, 1, 4, 9, 16, 25... are perfect squares.

```bash
Example 1:

Input: n = 13

Output: 2
Explanation: 13 = 4 + 9.

Example 2:

Input: n = 6

Output: 3
Explanation: 6 = 4 + 1 + 1.
```

Recursion:

```cpp
class Solution {
public:
    int numSquares(int n) {
        return dfs(n);
    }

private:
    int dfs(int target) {
        if (target == 0) {
            return 0;
        }

        int res = target;
        for (int i = 1; i * i <= target; i++) {
            res = min(res, 1 + dfs(target - i * i));
        }
        return res;
    }
};
```

### Unique Paths II
> You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 * (10^9).

```bash
Example 1:

Input: obstacleGrid = [[0,0,0],[0,0,0],[0,1,0]]

Output: 3
Explanation: There are three ways to reach the bottom-right corner:

Right -> Right -> Down -> Down
Right -> Down -> Right -> Down
Down -> Right -> Right -> Down
Example 2:

Input: obstacleGrid = [[0,0,0],[0,0,1],[0,1,0]]

Output: 0

```

Recursion
```cpp
class Solution {
    int M, N;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        M = obstacleGrid.size();
        N = obstacleGrid[0].size();
        return rr(0, 0, obstacleGrid);
    }

    int rr(int i, int j, vector<vector<int>>& ob) {
        // invalid case
        if (i >= M || j >= N)
            return 0;
        
        // if found
        if (i == M - 1 && j == N -1 )
            return 1;
        
        if (ob[i][j] == 1)
            return 0;
        
        // either right or down
        return rr(i, j+1, ob) + rr(i+1, j, ob);
    }
};
```

### Minimum Path Sum
> You are given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

```bash

Example 1:

Input: grid = [
    [1,2,0],
    [5,4,2],
    [1,1,3]
]

Output: 8
Explanation: The path with minimum sum is 1 -> 2 -> 0 -> 2 -> 3.

Example 2:

Input: grid = [
    [2,2],
    [1,0]
]

Output: 3
```

Recursion
```cpp
class Solution {
    int M, N;
public:
    int minPathSum(vector<vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();

        return rr(grid, 0, 0);     
    }

    int rr(vector<vector<int>>& grid, int i, int j) {
        if (i>= M || j >= N)
            return INT_MAX;
        
        if (i == M-1 && j == N -1)
            return grid[i][j];
        
        return grid[i][j] + min(rr(grid, i, j+1), rr(grid, i+1, j));
    }
};
```

### Last Stone Weight II
> You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose any two stones and smash them together. Suppose the stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the smallest possible weight of the left stone. If there are no stones left, return 0.

```bash
Example 1:

Input: stones = [2,4,1,5,6,3]

Output: 1
Explanation:

We smash 2 and 1 which makes the array [1,4,5,6,3].
We smash 4 and 3 which makes the array [1,1,5,6].
We smash 5 and 6 which makes the array [1,1,1].
We smash 1 and 1 which makes the array [1].
Example 2:

Input: stones = [4,4,1,7,10]

Output: 2
```

Apporach:
- Same as  [Min subset sum diff](#min-subset-sum-diff)
- for every example, actually certain elements are being added and certain elements are being subtracted
- for eg: 2 7 4 1 8 1
- => (8-7) (4-2) (1-1) lets say in first go we smashed these stones
- => 1 2 0 - in the second go we can smash 2 and 1 and weight of left stone will be 1 which is minimum
- => basically this is equivalent to (8-7) - (4-2) + (1-1) = 8 + 2 + 1 - 7 - 4 - 1
- => 8 + 2 + 1 - 7 - 4 - 1 this is equal to (8, 2, 1) - (7, 4, 1)
- => overall it is equal to dividing the stones array such that their difference is least - which gives us least weight
- therefore, this is exactly similar to minimum subset sum difference problem
- check   [Min subset sum diff](#min-subset-sum-diff)

### Edit Distance
> Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 
```bash
Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
```

Approach:
- Cant be solved using LCS since replace option is also there

Base:
- if (i == m) return n - j;
- if (j == n) return m - i;

Option:
- if same: ret dfs(i +1, j +1)
- Delete from word1: dfs(i + 1, j)
- Insert into word1: dfs(i, j + 1)
- Replace the character: dfs(i + 1, j + 1)

Recursion:
```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        return dfs(0, 0, word1, word2, m, n);
    }

    int dfs(int i, int j, string& word1, string& word2, int m, int n) {
        if (i == m) return n - j;
        if (j == n) return m - i;
        if (word1[i] == word2[j]){
            return dfs(i + 1, j + 1, word1, word2, m, n);
        }

        int res = min(dfs(i + 1, j, word1, word2, m, n),
                      dfs(i, j + 1, word1, word2, m, n));
        res = min(res, dfs(i + 1, j + 1, word1, word2, m, n));
        return res + 1;
    }
};
```

### Best Time to Buy and Sell Stock with Cooldown
> You are given an integer array prices where prices[i] is the price of NeetCoin on the ith day.

You may buy and sell one NeetCoin multiple times with the following restrictions:

After you sell your NeetCoin, you cannot buy another one on the next day (i.e., there is a cooldown period of one day).
You may only own at most one NeetCoin at a time.
You may complete as many transactions as you like.

Return the maximum profit you can achieve.

```bash
Example 1:

Input: prices = [1,3,4,0,4]

Output: 6
Explanation: Buy on day 0 (price = 1) and sell on day 1 (price = 3), profit = 3-1 = 2. Then buy on day 3 (price = 0) and sell on day 4 (price = 4), profit = 4-0 = 4. Total profit is 2 + 4 = 6.

Example 2:

Input: prices = [1]

Output: 0
```

Apporach:
- two choices at every node:
    1. cooldown
    2. Buy/Sell
        1. Buy only if earlier was sell or starting
        1. sell only if earlier was buy

Recursion
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // choice -> true : buy
        // choice -> false : sell
        return dfs(0, true, prices);
    }

private:
    int dfs(int i, bool choice, vector<int>& prices) {
        if (i >= prices.size())
            return 0;

        // Two choices :
        // 1. Cooldown i.e dont do anything
        // 2. B or S :
        //      S if only Bought earlier
        //      B if only sold earlier
        int cooldown = dfs(i + 1, choice, prices);

        // choice -> true : buy
        // choice -> false : sell
        if (choice) {
            // next choice will be sell or cooldown
            int buy = dfs(i + 1, !choice, prices) - prices[i];
            return max(buy, cooldown);
        } else {
            // next choice is to buy or cooldown
            int sell = dfs(i + 2, !choice, prices) + prices[i];
            return max(sell, cooldown);
        }
    }
};
```