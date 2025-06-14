# Backtracking Problems

### Problems
1. [Permutations of a String](#1-permutations-of-a-string)

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