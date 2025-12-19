# Arrays and Strings

### Problems
1. [KMP ALGO](#kmp-algo)
1. [Rotated Digits](#rotated-digits)


### KMP Algo
```cpp
void generate_lps(vector<int> &pattern, vector<int> &lps) {
    int prev_lps = 0;
    int i = 1;

    while (i < pattern.size()) {
        if (pattern[i] == lps[prev_lps]) {
            lps[i] = prev_lps + 1;
            prev_lps++;
            i++;
        } else {
            if (prev_lps == 0) {
                lps[i] = 0;
                i++;
            } else {
                prev_lps = lps[prev_lps - 1];
            }
        }
    }
}

void kmp(vector<int> &haystack, vector<int> &pattern) {

    int i = 0;  // ptr for hatystack
    int j = 0;  // ptr for needle

    vector<int> lps(pattern.size(), 0);
    generate_lps(pattern, lps);

    while (i < len(haystack)) {
        if (haystack[i] == pattern[i]) {
            i++;
            j++;
        } else {
            if (j == 0)
                i++;
            else
                j = lps[j - 1];
        }

        if (j == pattern.size())
            return i - patter.size();
    }

    return -1;
}
```

### Rotated Digits
> An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

0, 1, and 8 rotate to themselves,
2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
6 and 9 rotate to each other, and
the rest of the numbers do not rotate to any other number and become invalid.
Given an integer n, return the number of good integers in the range [1, n].

```bash
Example 1:

Input: n = 10
Output: 4
Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Example 2:

Input: n = 1
Output: 0
Example 3:

Input: n = 2
Output: 1
```
Approach:
* if a number has any digits 3,4,7 they are straight away not good return
* if they are valid check if they are good i,e 2,5,6,9
* return good if isvalid and is good.
* 10 -> is valid but not good

```cpp
class Solution {
public:
    int rotatedDigits(int n) {
        int res = 0;
        
        for (int i = 0; i <= n; i++) {
            int nm = i;
            bool isValid = true;
            bool isGood = false;
            while (nm) {
                int d = nm % 10;
                if (d == 3 || d == 4 || d == 7) {
                    isValid = false;
                    break;
                }
                if (d == 2 || d == 5 || d == 6 || d == 9)
                    isGood = true;
                nm /= 10;
            }

            if (isValid && isGood)
                res++;
        }

        return res;
    }
};
```