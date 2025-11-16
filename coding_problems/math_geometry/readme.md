# Math and Geometry Problems

1. [Non Cyclical Number](#1-no-cyclical-number)

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