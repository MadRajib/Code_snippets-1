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
    else if t[i+1][j] > t[i][j+1], store text1[i] i = i++; 
    else store text2[j] j++; 

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
- inserstion  = text1.len - LCS
- deletion = text2.len - LCS
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