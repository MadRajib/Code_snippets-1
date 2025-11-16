# Math and Geometry Problems

1. [Non Cyclical Number](#1-no-cyclical-number)
1. [POW(x, n)](#2-pow)
1. [Rotate Image](#3-rotate-image)
1. [Spiral Matrix](#4-spiral-matrix)
1. [Set Matrix Zeroes](#5-set-matrix-zeroes)

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

### 3. Rotate Image
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

### 4. Spiral Matrix
> Given an m x n matrix of integers matrix, return a list of all elements within the matrix in spiral order.

```bash
Input: matrix = [[1,2],[3,4]]

Output: [1,2,4,3]

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]

Output: [1,2,3,6,9,8,7,4,5]

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]

Output: [1,2,3,4,8,12,11,10,9,5,6,7]

```

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int l =  0;
        int r = matrix[0].size() - 1;

        int t = 0, b = matrix.size() - 1;
        vector<int> res;

        while ( l <= r && t <= b) {

            for (int i = l; i <= r; i++)
                res.push_back(matrix[t][i]);
            /* next itr will be next row */
            t++;
            
            for (int i = t; i <= b; i++)
                res.push_back(matrix[i][r]);
            /* same condition */
            r--;

            // to handle single row or col matrix
            // coz for them nothing more is required!
            if (!((l <= r) && (t <= b)))
                break;
    
            for (int i = r; i >= l; i--)
                res.push_back(matrix[b][i]);
            b--;

            for (int i = b; i >= t; i--)
                res.push_back(matrix[i][l]);
            l++;
        }

        return res;
    }
};
```

### 5. Set Matrix Zeroes
> Given an m x n matrix of integers matrix, if an element is 0, set its entire row and column to 0's.

You must update the matrix in-place.

Follow up: Could you solve it using O(1) space?

```bash
Input: matrix = [
  [0,1],
  [1,0]
]

Output: [
  [0,0],
  [0,0]
]

Input: matrix = [
  [1,2,3],
  [4,0,5],
  [6,7,8]
]

Output: [
  [1,0,3],
  [0,0,0],
  [6,0,8]
]
```

Approach:

* Create two extra array for row and col of size n and m to store flags
* if a element is 0 we set the which row and col to set 0 in these two arrays
* then we iterate over the matrix again, checking if row flag or col flag is set, if yes then zero it out.

* Now to not use extra space, we can use the first row as col flag array.
* but for we cannot use the first col since, 1 element i,e [0][0] is already occupied by col flag array.
* we will create an extra variable to store flag of first row, and for rows > 0 will be stored in first col
from 1 to n.
* Then the approach is same, we iterate throw r = 1 to rows and c = 1 to cols.
* at last we check if we need to clear 1st colum by checking if cols flag array's [0] i.e matrix[0][0] is zeroed or not.
* next we need to take care of the first row by checking if the extra variable flag is set or not.

```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        bool extr_cel = false;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (!matrix[r][c]) {
                    matrix[0][c] = 0;
                    if (r > 0)
                        matrix[r][0] = 0;
                    else
                        extr_cel = true;
                }
            }
        }

        for (int r = 1; r < rows; r++) {
            for (int c = 1; c < cols; c++) {
                if (!matrix[r][0] || !matrix[0][c]) {
                    matrix[r][c] = 0;
                }
            }
        }

        if (!matrix[0][0]) {
            for (int r = 0; r < rows; r++)
                matrix[r][0] = 0;
        }
        
        if (extr_cel) {
            for (int c = 0; c < cols; c++)
                matrix[0][c] = 0;
        }
    }
};

```