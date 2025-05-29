# Sliding window Problems

## Fixed size sliding win problems
### Aproach
    1. While iterating save the value or index
    2. if win size if reached store the res based on conditon and reduce win size
    3. Return the res

### 1. Max Sum Subarray of size K
> Given an array of integers arr[]  and a number k. Return the maximum sum of a subarray of size k.
```bash
Input: arr[] = [100, 200, 300, 400] , k = 2
Output: 700
Explanation: arr3  + arr4 = 700, which is maximum.
Input: arr[] = [100, 200, 300, 400] , k = 4
Output: 1000
Explanation: arr1 + arr2 + arr3 + arr4 = 1000, which is maximum.
```

```cpp
    int maximumSumSubarray(vector<int>& arr, int k) {
        // code here
        int s = 0;
        int max_sm = 0;
        int sm = 0;
        for (int i = 0; i < arr.size(); i++) {
            sm += arr[i];
            /* Check if win size is reached*/
            if (i - s + 1 == k) {
               max_sm = max(max_sm, sm);
               sm -= arr[s];
               s++;
            }
        }
        
        return max_sm;
    }
```

### 2. First negative in every window of size k
> Given an array arr[]  and a positive integer k, find the first negative integer for each and every window(contiguous subarray) of size k.

> Note: If a window does not contain a negative integer, then return 0 for that window.
```bash
Input: arr[] = [-8, 2, 3, -6, 10] , k = 2
Output: [-8, 0, -6, -6]
Explanation:
Window [-8, 2] First negative integer is -8.
Window [2, 3] No negative integers, output is 0.
Window [3, -6] First negative integer is -6.
Window [-6, 10] First negative integer is -6.


Input: arr[] = [12, -1, -7, 8, -15, 30, 16, 28] , k = 3
Output: [-1, -1, -7, -15, -15, 0] 
Explanation:
Window [12, -1, -7] First negative integer is -1.
Window [-1, -7, 8] First negative integer is -1.
Window [-7, 8, -15] First negative integer is -7.
Window [8, -15, 30] First negative integer is -15.
Window [-15, 30, 16] First negative integer is -15.
Window [30, 16, 28] No negative integers, output is 0.
```

```cpp
vector<int> firstNegInt(vector<int>& arr, int k) {
        // write code here
        vector<int> res(arr.size() - k + 1);
        int l = arr.size() - 1;
        
        int j = res.size() - 1;
        int prev = -1;
        
        /*Iterate from the last as we have to store the first negative */
        for (int i = l; i >= 0; i--) {
            /*store the last negative seen */
            if (arr[i] < 0)
                prev = i;

            /* if win sz k is hit store last neg and reduce windows from end */
            if (l - i + 1 == k) {

                /* store the res from the last in result vector*/
                if (prev > -1)
                    res[j] = arr[prev];
                else
                    res[j] = 0;
                
                /* check if last remove element is prev neg no then set it to -1 */
                if (prev == l)
                    prev = -1;

                /* go to next result location*/
                j--;
                
                l--;
            }
        }

        return res;
    }
```

### 3. Count Occurences of Anagrams
> Given a word pat and a text txt. Return the count of the occurrences of anagrams of the word in the text.
```bash
Input: txt = "forxxorfxdofr", pat = "for"
Output: 3
Explanation: for, orf and ofr appears in the txt, hence answer is 3.

Input: txt = "aabaabaa", pat = "aaba"
Output: 4
Explanation: aaba is present 4 times in txt.
```
1. Use map to 
```cpp
int search(string &pat, string &txt) {
        // code here
        unordered_map<int, int> mp;
        
        int letter_count = 0;
        int l = 0;
        int res = 0;
        
        for (int i =0; i < pat.length(); i++)
            mp[pat[i]]++;
        
        /* Count is to indicated total nof chars already seen */
        letter_count = mp.size();
        
        for (int i = 0; i < txt.length(); i++) {

            /* Process only those chars present in the pattern */
            if (mp.find(txt[i]) != mp.end()) {
                mp[txt[i]]--;
                if (mp[txt[i]] == 0)
                    letter_count--;
            }
            
            if (i - l + 1 ==  pat.length()) {
                if (letter_count == 0)
                    res++;
                /* process only chars present in pattern */
                if (mp.find(txt[l]) != mp.end()) {

                    /* only increment the count if removed char count was zero */
                    if (mp[txt[l]] == 0 ){
                        letter_count++;
                    }
                    
                    mp[txt[l]]++;
                }
                
                l++;
            }
        }
        
        return res;
    }
```

### 4. (239.) Sliding Window Maximum
> You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.
```bash
Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:

Input: nums = [1], k = 1
Output: [1]
```
1. Use map to 
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> l_max;
        vector<int> res;
        int s = 0;
        int i = 0;
        for (; i < nums.size(); i++) {
            /* Remove no that are smaller than current element since they dont have the chance to be part of the result*/
            while(!l_max.empty() && (l_max.back() < nums[i]))
                l_max.pop_back();
            /* save the current element > or less than stack back */
            l_max.push_back(nums[i]);

            if (i - s + 1 == k) {
                res.push_back(l_max.front());
                /* check if removed element is first in the dequeue */
                if (l_max.front() == nums[s])
                        l_max.pop_front();
                s++;
            }
        }
        return res;
    }
```

## Variable size sliding win problems
### Aproach
    1. Have a counter or hash-map to count specific array input and keep on increasing the window toward right using outer loop.
    2. Have a while loop inside to reduce the window side by sliding toward right. Movement will be based on constraints of problem.
    3. Store the current maximum window size or minimum window size or number of windows based on problem requirement.

### 1. Longest Substring with K Uniques
> Given a string s, you need to print the size of the longest possible substring with exactly k unique characters. If no possible substring exists, print -1.

```bash
Examples:

Input: s = "aabacbebebe", k = 3
Output: 7
Explanation: "cbebebe" is the longest substring with 3 distinct characters.

Input: s = "aaaa", k = 2
Output: -1
Explanation: There's no substring with 2 distinct characters.

Input: s = "aabaaab", k = 2
Output: 7
Explanation: "aabaaab" is the longest substring with 2 distinct characters.
```

```cpp
 int longestKSubstr(string &s, int k) {
        // your code here
        int res = -1;
        int l = 0;
        unordered_map<int, int> mp;
        
        for (int i = 0; i< s.length(); i++) {
            mp[s[i]]++;
            /* check for condition if invalid reduce the window */
            while (mp.size() > k) {
                mp[s[l]]--;
                if (mp[s[l]] == 0)
                    mp.erase(s[l]);
                l++;
            }
            /* if condition is valid store the result and increase window */
            if (mp.size() == k)
                res = max(res, i - l + 1);
        }
        
        return res;
    }
```

### 2. (3.) Longest Substring Without Repeating Characters
> Given a string s, find the length of the longest substring without duplicate characters.

```bash
Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```
```cpp
int lengthOfLongestSubstring(string s) {
        unordered_map<int, int> mp;
        int l = 0;
        int res = 0;

        for (int i = 0; i < s.length(); i++) {
            mp[s[i]]++;

            while ( l < s.length() && mp[s[i]] > 1) {
                mp[s[l]]--;
                l++;
            }

            res = max(res, i - l + 1);
        }

        return res;
}
```

### 3. (904.) Fruit Into Baskets
You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

You only have two baskets, and each basket can only hold a single type of fruit. There is no limit on the amount of fruit each basket can hold.
Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
Given the integer array fruits, return the maximum number of fruits you can pick.

```bash
Example 1:

Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.

Example 2:

Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:

Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
```

```cpp
int totalFruit(vector<int>& fruits) {
        int j = 0;
        int res = 0;
        unordered_map<int, int> mp;
        for (int i = 0; i < fruits.size(); i ++) {
            mp[fruits[i]]++;

            while (j < fruits.size() && mp.size() > 2) {
                mp[fruits[j]]--;
                if (mp[fruits[j]] == 0)
                    mp.erase(fruits[j]);
                j++;
            }

            res = max(res, i - j +1);
        }

        return res;
    }
```

### 4. (209.) Minimum Size Subarray Sum
> Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

```bash
Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
```

```cpp
int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0;
        int res = INT_MAX;
        int sm = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            sm += nums[i];

            /* since invalid case is also valid here */
            while (l < nums.size() && sm > target) {
                res = min(res, i - l + 1);
                
                sm -= nums[l];
                l++;
            }

            if (sm == target)
                res = min(res, i - l + 1);
        }

        return res == INT_MAX? 0 : res;
    }
```

### 5. 76. Minimum Window Substring
>Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

```bash
Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
```

```cpp
    string minWindow(string s, string t) {
        unordered_map<char, int> mp, win;
        int l_min = 0;
        int r_min = 0;
        int match_count = 0;
        int min_len = s.length() + 1;
        int l = 0;

        if (t.length() > s.length() || s == "")
            return "";

        for (auto c: t)
            mp[c]++;
        
        for (int r = 0; r < s.length(); r++) {
            win[s[r]]++;

            /* increase matched chars if needed no.of letter found */
            if (mp.find(s[r]) != mp.end() && win[s[r]] == mp[s[r]])
                match_count++;
            
            while (match_count ==  mp.size()) {
                if (r - l + 1 < min_len) {
                    l_min = l;
                    r_min = r;
                    min_len = r_min - l_min + 1;
                }

                win[s[l]]--;
                if (mp.find(s[l]) != mp.end() && win[s[l]] < mp[s[l]])
                    match_count--;
                l++;
            }
        }

        if (min_len < s.length() + 1)
            return s.substr(l_min, min_len);
        return "";
    }
```
