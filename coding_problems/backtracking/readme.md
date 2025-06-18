# Backtracking Problems

### Problems
1. [Permutations of a String](#1-permutations-of-a-string)
1. [Subsets](#2-subsets)
1. [Subsets II](#3-subsets-ii)
1. [Palindrome Partitioning](#4-palindrome-partitioning)
1. [Letter Combinations of a Phone Number](#5-letter-combinations-of-a-phone-number)
1. [Combination Sum](#6-combination-sum)
1. [Combination Sum II](#7-combination-sum-ii)
1. [Word Search](#8-word-search) 

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

![example 1](problem_2.png)

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
### 3. Subsets II
> Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

```bash
Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
```

* Sort the array first, then skip the duplicated after traversing 

```cpp
class Solution {
    vector<vector<int>> res;
    vector<int> subs;
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
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

        while (i + 1 < nums.size() && nums[i] == nums[i + 1])
            i++;

        dfs(i + 1, nums);
    }
};
```

### 4. Palindrome Partitioning
> Given a string s, split s into substrings where every substring is a palindrome. Return all possible lists of palindromic substrings.
> You may return the solution in any order.
```bash
Example 1:

Input: s = "aab"

Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"

Output: [["a"]]
```
* Why pop > we want to resue one one partition list.
```cpp
class Solution {
public:
    vector<vector<string>> res;
    vector<string> part;
    vector<vector<string>> partition(string s) {
        res.clear();
        part.clear();

        dfs(0, s);

        return res;
    }

    void dfs( int p, string& s) {
        if (p >= s.length()) {
            res.push_back(part);
            return;
        }

        for ( int i = p; i < s.length(); i++) {
            if (isPalim(s, p, i)) {
                part.push_back(s.substr(p, i - p + 1));
                dfs(i + 1, s);
                part.pop_back();
            }
        }
    }

    bool isPalim(string& str, int s, int l) {
        while (s <= l) {
            if (str[s] != str[l])
                return false;
            s++;
            l--;
        }

        return true;
    }
};

```
### 5. Letter Combinations of a Phone Number
```bash
Example 1:

Input: digits = "34"

Output: ["dg","dh","di","eg","eh","ei","fg","fh","fi"]
Example 2:

Input: digits = ""

Output: []
```

```cpp
class Solution {
public:
    vector<string> res;
    vector<string> digitToChar = {"", "", "abc", "def", "ghi", "jkl", 
                                  "mno", "qprs", "tuv", "wxyz"};
    vector<string> letterCombinations(string digits) {
        res.clear();
        if (digits == "")
            return res;

        dfs(0, "", digits);

        return res;
    }

    void dfs(int s, string str, string& digits) {
        if (s >= digits.length()) {
            res.push_back(str);
            return;
        }

        for (auto c: digitToChar[digits[s] - '0']) {
            dfs(s + 1, str + c, digits);
        }

    }
};

```
### 6 Combination Sum
> You are given an array of distinct integers nums and a target integer target. Your task is to return a list of all unique combinations of nums where the chosen numbers sum to target.
> The same number may be chosen from nums an unlimited number of times. Two combinations are the same if the frequency of each of the chosen numbers is the same, otherwise they are different.
> You may return the combinations in any order and the order of the numbers in each combination can be in any order.
```bash
Example 1:

Input: 
nums = [2,5,6,9] 
target = 9

Output: [[2,2,5],[9]]
Explanation:
2 + 2 + 5 = 9. We use 2 twice, and 5 once.
9 = 9. We use 9 once.

Example 2:

Input: 
nums = [3,4,5]
target = 16

Output: [[3,3,3,3,4],[3,3,5,5],[4,4,4,4],[3,4,4,5]]
Example 3:

Input: 
nums = [3]
target = 5

Output: []
```

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> comb;
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        res.clear();
        comb.clear();

        dfs(0, target, nums);
        return res;
    }

    void dfs(int s, int target, vector<int>& nums) {

        if (target  == 0) {
            res.push_back(comb);
            return;
        }

        for (int i = s; i < nums.size(); i++) {
            if (nums[i] <= target) {
                comb.push_back(nums[i]);
                dfs(i, target - nums[i], nums);
                comb.pop_back();
            }
        }
    }
};

```
### 7 Combination Sum II

> You are given an array of integers candidates, which may contain duplicates, and a target integer target. Your task is to return a list of all unique combinations of candidates where the chosen numbers sum to target.
> Each element from candidates may be chosen at most once within a combination. The solution set must not contain duplicate combinations.
> You may return the combinations in any order and the order of the numbers in each combination can be in any order.

```bash
Example 1:

Input: candidates = [9,2,2,4,6,1,5], target = 8

Output: [
  [1,2,5],
  [2,2,4],
  [2,6]
]
Example 2:

Input: candidates = [1,2,3,4,5], target = 7

Output: [
  [1,2,4],
  [2,5],
  [3,4]
]
```

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> comb;
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        res.clear();
        comb.clear();
        sort(nums.begin(), nums.end());

        dfs(0, target, nums);
        return res;
    }

    void dfs(int s, int target, vector<int>& nums) {

        if (target == 0) {
            res.push_back(comb);
            return;
        }
        for (int i = s; i < nums.size(); i++) {
            if ( i > s && nums[i] == nums[i -1])
                continue;
            if (nums[i] <= target) {
                comb.push_back(nums[i]);
                dfs(i + 1, target - nums[i], nums);
                comb.pop_back();
            }
        }
    }
};
```
### 8 Word Search
> Given a 2-D grid of characters board and a string word, return true if the word is present in the grid, otherwise return false.
> For the word to be present it must be possible to form it with a path in the board with horizontally or vertically neighboring cells. The same cell may not be used more than once in a word.

```bash
Example 1:

Input: 
board = [
  ["A","B","C","D"],
  ["S","A","A","T"],
  ["A","C","A","E"]
],
word = "CAT"

Output: true
Example 2:



Input: 
board = [
  ["A","B","C","D"],
  ["S","A","A","T"],
  ["A","C","A","E"]
],
word = "BAT"

Output: false
```

* dont visit the node already visited, that why changed the char to '#'

```cpp
class Solution {
public:
    int rCount;
    int cCount;
    vector<vector<char>> board;
    string word;

    bool exist(vector<vector<char>>& board, string word) {
        this->board = board;
        rCount = board.size();
        cCount = board[0].size();
        this->word = word;

        for (int i = 0; i < rCount; i++) {
            for (int j = 0; j < cCount; j++) {
               if (dfs(i, j, 0))
                    return true;
            }
        }
        return false;
    }

    bool dfs(int r, int c, int i) {

        if (i == word.size())
            return true;

        if (r < 0 || c < 0 || r >= rCount || c >= cCount ||
            board[r][c] != word[i] || board[r][c] == '#')
            return false;

        board[r][c] = '#';

        bool res = dfs(r - 1, c, i + 1 ) ||
        dfs(r + 1, c, i + 1 ) ||
        dfs(r , c - 1, i + 1 ) ||
        dfs(r, c + 1, i + 1 );
        
        board[r][c] = word[i];

        return res;
    }
};

```
