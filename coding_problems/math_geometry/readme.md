# Math and Geometry Problems

1. [Non Cyclical Number](#1-no-cyclical-number)
1. [POW(x, n)](#2-pow)
1. [Rotate Image](#3-rotate-image)

TODO:
🔲 Binary exponent

### 1. Non Cyclical Number
> A non-cyclical number is an integer defined by the following algorithm:

* Given a positive integer, replace it with the sum of the squares of its digits.
* Repeat the above step until the number equals 1, or it loops infinitely in a cycle which does not include 1.
* If it stops at 1, then the number is a non-cyclical number.

Given a positive integer n, return true if it is a non-cyclical number, otherwise return false.

```bash
Input: n = 100

Output: true
Explanation: 1^2 + 0^2 + 0^2 = 1

Input: n = 101

Output: false
Explanation:
1^2 + 0^2 + 1^2 = 2
2^2 = 4
4^2 = 16
1^2 + 6^2 = 37
3^2 + 7^2 = 58
5^2 + 8^2 = 89
8^2 + 9^2 = 145
1^2 + 4^2 + 5^2 = 42
4^2 + 2^2 = 20
2^2 + 0^2 = 4 (This number has already been seen)
```

Apporach 1:
 * Use hash set to store the sumof digit

 ```cpp
 class Solution {
public:
    int getSum(int n) {
        int r = 0;
        int sm = 0;
        while (n) {
            r = n % 10;
            n = n / 10;
            sm += r * r;
        }

        return sm;
    }
    bool isHappy(int n) {
        unordered_map<int, int> mp;
        while (true) {
            n = getSum(n);
            if (n == 1)
                return true;
            else if (mp.find(n) != mp.end())
                return false;
            else
                mp[n] = 1;    
        }

        return false;
    }
};
```

Better Aproach:
    * Basically we are trying to find the cycle if it present then:
        * if the cycle is at 1 then its happy
        * else its not
    * We can use slow-fast algo of 2 pointers to solve this

```cpp
 class Solution {
public:
    int getSum(int n) {
        int r = 0;
        int sm = 0;
        while (n) {
            r = n % 10;
            n = n / 10;
            sm += r * r;
        }

        return sm;
    }
    bool isHappy(int n) {
        int slow = n, fast = getSum(n);

        while (slow != fast) {
            // step twice at a time
            fast = getSum(fast);
            fast = getSum(fast);

            // Step once at a time
            slow = getSum(slow);
        }

        return slow == 1;
    }
};
```

### 2. POW
> Pow(x, n) is a mathematical function to calculate the value of x raised to the power of n (i.e., x^n).

Given a floating-point value x and an integer value n, implement the myPow(x, n) function, which calculates x raised to the power n.

You may not use any built-in library functions.

```bash
Example 1:

Input: x = 2.00000, n = 5

Output: 32.00000
Example 2:

Input: x = 1.10000, n = 10

Output: 2.59374
Example 3:

Input: x = 2.00000, n = -3

Output: 0.12500
```

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0) {
            return 0;
        }
        if (n == 0) {
            return 1;
        }

        double res = 1;
        for (int i = 0; i < abs(n); i++) {
            res *= x;
        }
        return n >= 0 ? res : 1 / res;
    }
};
```
* divide and conquor.
* We caculate the half first then mult it with itself;

Binary Exponentiation Recursion
```cpp
class Solution {
public:

    double helper(double x, int n) {
        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        
        double half = helper(x, n / 2);
        half *= half;
        return (n % 2)? half * x: half;
    }

    double myPow(double x, int n) {
        double res = 1;
        if (x == 0)
            return 0;

        if (n == 0)
            return 1;
        
        res = helper(x , n);

        return (n < 0)? 1/res: res; 
    }
};
```

### 4. Rotate Image
> Given a square n x n matrix of integers matrix, rotate it by 90 degrees clockwise.

You must rotate the matrix in-place. Do not allocate another 2D matrix and do the rotation.

```bash
Input: matrix = [
  [1,2],
  [3,4]
]

Output: [
  [3,1],
  [4,2]
]

Input: matrix = [
  [1,2,3],
  [4,5,6],
  [7,8,9]
]

Output: [
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
```
Appirach:
 * we will create a boundary t,b, l and r
 * we will rotate 4 elements at a time of each corner
 * for square we will rotate all the elements in side that boundary -1, since last element is already rotated.
 * then reduce the boundary


refer [video](https://neetcode.io/problems/rotate-matrix?list=neetcode150)

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int l =  0;
        int r = matrix.size() - 1;
        int t = l, b = r;
        int tl;
        while (l < r) {
            // i will iterate for n - 1 element in that boundary
            // because last element is already rotated
            // since i starts at 0 at max it can go till n - 2 i,e 0 < i < (r - l + 1) - 1
            for (int i = 0; i < r - l; i++) {
                tl = matrix[t][l + i];

                matrix[t][l + i] = matrix[b - i][l];
                matrix[b - i][l] = matrix[b][r - i];
                matrix[b][r - i] = matrix[t + i][r];
                matrix[t + i][r] = tl;
            }

            // reduce the boundary
            l++;
            r--;

            t++;
            b--;
        }

    }
};
```
Variation: Rotate in alternate way
```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int l =  0;
        int r = matrix.size() - 1;
        int t = l, b = r;
        int tl;
        bool toggle = false;
        while (l < r) {
            // i will iterate for n - 1 element in that boundary
            // because last element is already rotated
            // since i starts at 0 at max it can go till n - 2 i,e 0 < i < (r - l + 1) - 1
            for (int i = 0; i < r - l; i++) {
                tl = matrix[t][l + i];

                // CW
                if (!toggle) {
                    matrix[t][l + i] = matrix[b - i][l];
                    matrix[b - i][l] = matrix[b][r - i];
                    matrix[b][r - i] = matrix[t + i][r];
                    matrix[t + i][r] = tl;
                } else {
                    // CCW
                    matrix[t][l + i] = matrix[t + i][r];
                    matrix[t + i][r] = matrix[b][r - i];
                    matrix[b][r - i] = matrix[b - i][l];
                    matrix[b - i][l] = tl;
                }
            }

            toggle = !toggle;

            // reduce the boundary
            l++;
            r--;

            t++;
            b--;
        }

    }
};
```