# Backtracking Problems

### Problems
1. [Permutations of a String](#1-permutations-of-a-string)
1. [Subsets](#2-subsets)

Identification :
    
* chocies + decision.
* all combinations.
* controlled recursion.
* number of choices.
* size of constraints.
* don't be greedy.

### 1. Permutations of a String
> Given a string s, which may contain duplicate characters, your task is to generate and return an array of all unique permutations of the string. You can return your answer in any order.

```bash
Examples:

Input: s = "ABC"
Output: ["ABC", "ACB", "BAC", "BCA", "CAB", "CBA"]
Explanation: Given string ABC has 6 unique permutations.
Input: s = "ABSG"
Output: ["ABGS", "ABSG", "AGBS", "AGSB", "ASBG", "ASGB", "BAGS", "BASG", "BGAS", "BGSA", "BSAG", "BSGA", "GABS", "GASB", "GBAS", "GBSA", "GSAB", "GSBA", "SABG", "SAGB", "SBAG", "SBGA", "SGAB", "SGBA"]
Explanation: Given string ABSG has 24 unique permutations.
Input: s = "AAA"
Output: ["AAA"]
Explanation: No other unique permutations can be formed as all the characters are same.
```

Observation

* To make it unique don't include the character if already decided in same choice loop

![example 1](permutation_of_string_recursion_tree_eg_1.jpg)
![example 2](permutation_of_string_recursion_tree_eg_2.jpg)

```cpp
class Solution {
  public:
    vector<string> findPermutation(string &s) {
        // Code here there
        
        vector<string> res;
        string op = "";
        
        permute(s, op, res);
        
        return res;
    }
    
    void permute(string ip, string op, vector<string> &res) {
        if (ip.length() == 0) {
            res.push_back(op);
            return;
        }
        
        unordered_map<char, bool> mp;
        
        // choice loop
        for (int i = 0; i < ip.length(); i++) {
            
            if (mp.find(ip[i]) == mp.end()) {
                mp[ip[i]] = true;
                string _op = op + ip[i];
                string _ip = ip.substr(0, i) + ip.substr(i+1);
                permute(_ip, _op, res);
            }
        }
    }
};

```

### 2. Subsets
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
* Choices : either include s[i] or exclude and move to next num
* While returning save the subsets.
*  
```cpp
class Solution {
    vector<int> subs;
    vector<vector<int>> res;
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        
        res.clear();
        subs.clear();

        dfs(0, nums);

        return res;
    }

    void dfs(int i, vector<int>& nums) {

        if (i >= nums.size()) {
            res.push_back(subs);
            return;
        }

        subs.push_back(nums[i]);
        dfs(i + 1, nums);
        subs.pop_back();
        dfs(i + 1, nums);
    }
};
```
