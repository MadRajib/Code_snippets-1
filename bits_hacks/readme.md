## Bit Hacks

[reference](https://graphics.stanford.edu/~seander/bithacks.html)

1. [Tips](#tips)
    1. [Properties](#properties)
    1. [Check kth bit](#check-kth-bit)
    1. [Set kth bit](#set-kth-bith-in-a-word-x-to-1)
    1. [Clear kth bit](#clear-the-kth-bit-in-a-word-x)
    1. [Toggle kth bit](#toggle-the-kth-bit)
    1. [Remove Last set bit](#remove-the-last-set-bit)
    1. [Mask of last set bit](#compute-the-mask-of-the-least-significant--in-word)
    1. [Extract a bit field from a word x](#extract-a-bit-field-from-a-word-x)
    1. [Set a bit field in word x to a valye y](#set-a-bit-field-in-word-x-to-a-valye-y)
1. [Swap two integers](#swap-two-integers)
1. [Min of two integers](#min-of-two-integers)
1. [Modular Addition](#modular-addition)
1. [Round up to a Power of 2](#round-up-to-a-power-of-2)
1. [Counting bits set](#counting-bits-set)
1. [Find most significant set bit of a number](#find-most-significant-set-bit-of-a-number)
1. [Check if a no is power of 2](#check-if-a-no-is-power-of-2)
1. [Check if a no is power of 4](#to-check-power-of-4)
1. [Check if a no is power of 8](#check-for-power-of-8)
1. [Find Xor of a number without using XOR operator](#find-xor-of-a-number-without-using-xor-operator)
1. [Add 1 to an interger](#add-1-to-an-interger)
1. [Odd or even](#odd-or-even)
1. [Count the consecutive zero bits (trailing) on the right linearly](#count-the-consecutive-zero-bits-trailing-on-the-right-linearly)
1. [Single Number III](#single-number-iii)
1. [Convert Uppercase to LowerCase](#convert-uppercase-to-lowercase)
1. [Convert Lower to upper](#convert-lower-to-upper)
1. [Invert Alphabet Case](#invert-alphabet-case)
1. [Letter Position In alphabet](#letter-position-in-alphabet)
1. [Calculate XOR from 1 to n](#calculate-xor-from-1-to-n)
1. [Find XOR of numbers from the start to end](#find-xor-of-numbers-from-the-start-to-end)
1. [Count Number of bits to be flipped to convert A to B](#count-number-of-bits-to-be-flipped-to-convert-a-to-b)
1. [Swap all even and odd bits](#swap-all-even-and-odd-bits)
1. [Divide two integers without using mult, div or mod](#divide-two-integers-without-using-mult-div-or-mod)
1. [SINGLE NUMBER II](#single-number-ii)
1. [Determine if two ints are equal or not](#determine-if-two-ints-are-equal-or-not)
1. [Detect if two integers have opposite sign](#detect-if-two-integers-have-opposite-sign)
1. [Reduce a Number to 1](#reduce-a-number-to-1)
1. [Set mismatch](#set-mismatch)
1. [Maximum Product of Word Lengths](#maximum-product-of-word-lengths)
1. [Check If a String Contains All Binary Codes of Size K](#check-if-a-string-contains-all-binary-codes-of-size-k)

### Tips

#### Properties
```c
x = 0xb011011000
~x = 0xb100100111
-x = 0xb100101000

// since we have
x + ~x = -1;
-x = ~x + 1;
```

#### Check kth bit
```c
  mask = 1 << k;
  return x & mask
```

#### Set kth bith in a word x to 1.
```c
y = x | (1 << k)
```

#### Clear the kth bit in a word x.
```c
y = x & ~(1 << k)
```

#### Toggle the kth bit
```c
y = x ^ (1 << k)
```

#### Remove the last set bit
```c
x = x & (x - 1)
```
#### Compute the mask of the least-significant ! in word".
```c
r = x & (-x);
```

#### Extract a bit field from a word x
- mask and shift
```c
(x & mask) >> shift
```

#### Set a bit field in word x to a valye y.
- invert mask to clear, and OR the shifted value.
```c
x = (x & ~mask) | ((y << shift) & mask)
```

### Swap two integers
```c
x = x ^ y
y = x ^ y
x = x ^ y
```
-> poor at explotiting intruction level parallelism (ILP)

### Min of two integers
```c
r = (x < y) ? x: y;
```
* a mispredicted branch empties the processor pipeline

#### No Branch Prediction:
```c
r = y ^ ((x ^ y) & -(x < y));
```

* The C language represents the Booleans TRUE and
FALSE with the integers 1 and 0, respectively.
* If x < y, then -(x < y) => 1, which is all 1's in
two’s complement representation. Therefore, we
have y ^ (x ^ y) => x.
* If x >= y, then -(x < y) => 0. Therefore, we have
y ^ 0 => y.

### Modular Addition
Compute (!%+ ") mod #, assuming that $%! !%< #%
and $%! "%< #.

```c
r = (x + y) % n;

z = x + y;
r = (z < n) ? z : z - n;
```

Sol:
```c
z = x + y;
r = z - (n & -(z >= n));
```

### Round up to a Power of 2
Compute 2 [lg n]

sol:
```c
uint64_t n;
                    0010000001010000
--n;
n |= n >> 1;        0010000001001111
n |= n >> 1;        0011000001101111
n |= n >> 2;        0011100001111111
n |= n >> 4;        0011110001111111
n |= n >> 8;        0011111111111111
n |= n >> 16;       0011111111111111
n |= n >> 32;       0100000000000000 // populates all bits to right with 1
++n         // adjust to substruction done earlier
```

### Counting bits set

- Navie Way
```c
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v

for (c = 0; v; v >>= 1)
{
  c += v & 1;
}
```
The naive approach requires one iteration per bit, until no more bits are set. So on a 32-bit word with only the high set, it will go through 32 iterations.

- Brian Kernighan's way
```c
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v
for (c = 0; v; c++)
{
  v &= v - 1; // clear the least significant bit set
}
```

### Find most significant set bit of a number
```c
// O(log n)
int setBitNumber(int n)
{
    if (n == 0)
        return 0;

    int msb = 0;
    n = n / 2;
    while (n != 0) {
        n = n / 2;
        msb++;
    }

    return (1 << msb);
}
```

### Check if a no is power of 2
```c
x     = 010000 // all power of 2 have this format
x - 1 = 001111

(x & x - 1) -> 0 then its power of two.
```

### To check power of 4
- must ensure two conditions:
  1. The number is a power of 2
    * only one bit set
    * n & (n - 1) == 0
 1. The single 1 bit must be in an even bit position
    * (0, 2, 4, 6 … for 1-indexed positions)
```c
int isPowerOfFour(int n) {
    if (n <= 0) return 0;

    // Check power of 2: only one bit set
    if (n & (n - 1)) return 0;

    // Check that the 1-bit is in an even position
    // Mask: 0x55555555 = binary pattern 0101...0101
    return (n & 0x55555555) == n;
}
```
### Check for Power of 8
1. The number is a power of 2
2. Trailing zeros should be multiple of 3 
```c
int isPowerOfEight(unsigned int n) {
    if (n == 0) return 0;

    // Check power of 2
    if (n & (n - 1)) return 0;

    // Check bit in position multiple of 3
    // 0000 1001 0010 0100 1001 0010 0100 1001
    return (n & 0x09249249) == n;
}
```
### Find Xor of a number without using XOR operator
```c
x ^ y = x~y + ~xy
```

### Add 1 to an interger
- without using +, -, /, ++, --

Logic:
  1. Flip the last bit a ^ 1
  2. if the last bit is 1 propagate the carry.
```c
int add_one(int a) {
    int carry = 1; // we want to add 1
    while (carry != 0) {
        int temp = a ^ carry;        // add without carry
        carry = (a & carry) << 1;    // compute new carry
        a = temp;
    }
    return a;
}
```
or
```c
// using the property -x = ~x + 1
x + 1 = -(~x)
```

### Odd or even
```c
return (x & 1)? false: true;

return ((x >> 1) << 1) ==  x
```

### Count the consecutive zero bits (trailing) on the right linearly
```c
unsigned int v;  // input to count trailing zero bits
int c;  // output: c will count v's trailing zero bits,
        // so if v is 1101000 (base 2), then c will be 3

v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
for (c = 0; v; c++)
  v >>= 1;

```

### Single Number III
> Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.

```bash
Example 1:

Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Example 2:

Input: nums = [-1,0]
Output: [-1,0]

Example 3:

Input: nums = [0,1]
Output: [1,0]
```

Apporach:
- After xor all the nums we will be left with no with two no in the xr.
- Find the mask of last set bit in xr. 
- xor all nums which have this bit set, this will give the first no.
  - this remove all the dups no

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        long long xr = 0;
        for (auto n: nums)
            xr ^= n;
        
        long long mask = xr & -xr;
        int x = 0;
        for (auto n: nums) {
            if ((n & mask) > 0)
                x ^= n;
        }

        return {x, (int)xr^x};
    }
};
```

### Convert Uppercase to LowerCase
```c
  return (char)(ch | ' ');  // oring with space 32
```

### Convert Lower to upper
```c
  return (char)(ch & '_');
```

### Invert Alphabet Case
```c
  return (char)(ch ^ ' '); // 32
```

### Letter Position In alphabet
```c
  return (ch & 31) ; // works with both small and upper case.
```

### Calculate XOR from 1 to n

Obeservation
```bash
1     = 1
1 ^ 2 = 3
3 ^ 3 = 0
0 ^ 4 = 4
4 ^ 5 = 1
1 ^ 6 = 7
7 ^ 7 = 0
0 ^ 8 = 8
8 ^ 9 = 1
1 ^ 10 = 11
11 ^ 11 = 0
0 ^ 12 = 12
```
- if n % 4 == 0 -> n
- if n % 4 == 1 -> 1
- if n % 4 == 2 -> n + 1
- if n % 4 == 3 -> 0

```c
int findXOR(int n) {
  int m = n % 4;
  switch(m) {
    case 0:
      return n;
    case 1:
      return 1;
    case 2:
      return n + 1;
    case 3:
      return 0;
  }

  return -1;
} 
```

### Find XOR of numbers from the start to end

Apporach
- findXOR(start - 1) ^ findXOR(end)

### Count Number of bits to be flipped to convert A to B

```c
  xr = A ^ B
  return count_bits(xr);
```

### Swap ith and jth bit

- i and j from 1...
```c
  // store bits from i and j
  a = (x >> (i - 1)) && 1;
  b = (x >> (j - 1)) && 1;

  temp = a ^ b;

  // xor with loc i and j since it will remove previous bit value and place the new one
  x = x ^ (temp << (i - 1));
  x = x ^ (temp << (j - 1));

  return x;

```

### Swap all even and odd bits

```c
  e_bits = x & 0xAAAAAAAA;
  o_bits = x & 0x55555555;

  return (e_bits >> 1) | (o_bits << 1 );
```

### Toggle Bits from L to R

```c
  // set bits in that range to all ones
  mask =  (1 << (R - L + 1)) - 1;
  // move the range bits to that location
  mask = mask << (L - 1);

  return x ^ mask;
```

### Divide two integers without using mult, div or mod

Apporach 1 using Subtracktion:
- keep subtracking the diviso from the dividend until dividend becomes smaller than divisor.

Apporach 2 using Bit Manipulation:
```c

// dividen 30 divisor 4
// 30 = 4 * 2^2 + 4 * 2^1 + 4 * 2^0 + 2
// for each bit set subtract divisor shifteed to that pos if less than dividend.
// ORRed all the bit position as we go allong.

for (int i = 31; i >= 0; --i) {
    // Check if (divisor << i) <= dividend
    if ((b << i) <= a) {
      a -= (b << i);
      quotient |= (1LL << i);
  }
}
```

### SINGLE NUMBER II
> Given an integer array nums where every element appears thrice times except for one, which appears exactly once. Find the single element and return it.

Appraoch:
  - We are counting no of bits occurred in two variables ones and twos,
  - i,e mod of 3.
  ```c
    1:
      ones = (0 ^ 1) & ~(twos=0)    // ones = 1, twos = 0
      // if added to ones dont add to twos
      twos = (0 ^ 1) & ~(ones)      // ones = 1, twos = 0.
    1:
      ones = (1 ^ 1) & ~(twos=0)    // ones = 0, twos = 0.
      twos = (0 ^ 1) & ~(ones=0)    // ones = 0, twos = 1
    1.
      ones = (0 ^ 1) & ~(twos = 1)  // ones = 0, twos = 1
      twos = (1 ^ 1) & ~(ones = 0)  // ones = 0, twos = 0
  ```

```c
  int ones = 0;
  int twos = 0;

  for (int i = 0; i < n; i++) {
    ones = (ones ^ nums[i]) & ~(twos);
    twos = (twos ^ nums[i]) & ~(ones);
  }

  return ones;
```
### Determine if two ints are equal or not

Apporach
- XOR : return (a ^ b) == 0;
- AND : return (a & ~b) == 0;

### Detect if two integers have opposite sign

Apporach:
- Xor of two opposite number will give a negative number
```c
  return (a ^ b) < 0;
```

### Reduce a Number to 1
> Given a number, our task is to reduce the given number N to 1 in the minimum number of steps.

We can perform two types of operations in each step:

- Operation 1: If the number is even then divide the number by 2
- Operation 2: If the number is odd, then we are allowed to either (N+1) or (N-1)

Approach recursion:
```c
int func(int n) {
  if (n == 1)
      return 0;
  
  if (n % 2 == 0)
    return 1 + func(n/2);

  return 1 + min(func(n -1), func(n + 1));
}
```

Approch 2:
- every even no can be represented as 4x or 4x + 2;
- every odd no can be represented as 4x + 1 or 4x + 3;

```c
int count(int n) {
  int cnt = 0;
  while (n > 1) {
    cnt++;

    if ((n & 1) == 0) // even
      n >>= 1;  // divide by 2;
    // odd, n % 4 == 1 or n == 3(edge case), decrement - 1
    else if (n & 3 == 1 || (n == 3))
      n -= 1;
    // n % 4 == 3, increment +1
    else if ((n & 3) == 3)
      n += 1
  }

  return count;
}
```

### Set mismatch
> You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

```bash
Example 1:

Input: nums = [1,2,2,4]
Output: [2,3]

Example 2:

Input: nums = [1,1]
Output: [1,2]
```

Apporach 1:
- sum of n elements(S)  -> n(n + 1)/2;
- sum of square of n element(P) -> n(n+1)(2*n + 1)/6;
- S - s = x - y (s actuall array sum)
- P - p = (x + y)(x - y)  (p actuall square sum of elements)
- x and y are the corrupted nums

```cpp
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        long long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
        long long n = nums.size();

        for(int i : nums){
            s2 += i;
            s4 += i * i;
        }

        s1 = n * (n + 1) / 2;
        s3 = n * (n + 1) * (2 * n + 1) / 6;

        int dup = ((s2 - s1) + (s4 - s3) / (s2 - s1)) / 2;
        int mis = dup - (s2 - s1);

        return {dup, mis};
    }
};
```

Approach XOR Operation:
- Calculate the XOR of all numbers from 1 to n
- Xor all the nums in that array with the previous xor value
- at last we will only have two required number in that xor value (xr).
- Find the mask of last set bit in xr.
- xor all nums which have this bit set form 1 to n and from array, this will give the first no.
  - this remove all the dups no

```cpp

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        int xorAll = 0;
        int xorArray = 0;

     
        for (int i = 1; i <= n; i++) {
            xorAll ^= i;
        }

        
        for (int num : nums) {
            xorArray ^= num;
        }

       
        int xorResult = xorArray ^ xorAll;

        
        int rightmostSetBit = xorResult & -xorResult;

        int xorSet = 0;
        int xorNotSet = 0;

        
        for (int i = 1; i <= n; i++) {
            if (i & rightmostSetBit) {
                xorSet ^= i;
            } else {
                xorNotSet ^= i;
            }
        }

        for (int num : nums) {
            if (num & rightmostSetBit) {
                xorSet ^= num;
            } else {
                xorNotSet ^= num;
            }
        }

        
        for (int num : nums) {
            if (num == xorSet) {
                return {xorSet, xorNotSet};
            }
        }

        
        return {xorNotSet, xorSet};
    }
};
```

### Maximum Product of Word Lengths
> Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. If no such two words exist, return 0.

```bash
Example 1:

Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".

Example 2:

Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4
Explanation: The two words can be "ab", "cd".

Example 3:

Input: words = ["a","aa","aaa","aaaa"]
Output: 0
Explanation: No such pair of words.
```

Apporach:
- conver string to bits a -> 1st bit set b 2nd

```cpp
int maxProduct(vector<string>& words) {
  int n = words.size();
  int ans = 0;
  vector<int> state(n);

  for(int i=0;i<n;i++){
    for(char ch:words[i]){
      //set the bits corresponding to the particular character
      state[i] |= 1<<(ch-'a');
    }

    for(int j=0;j<i;j++){
      //if no common letter between two strings, then find
      if(!(state[i] & state[j])){
        int currans = words[i].size()* words[j].size();
        ans = max(ans,currans);
      }
    }
}
```
### Check If a String Contains All Binary Codes of Size K
Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.

```bash
Example 1:

Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.

Example 2:

Input: s = "0110", k = 1
Output: true
Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring. 

Example 3:

Input: s = "0110", k = 2
Output: false
Explanation: The binary code "00" is of length 2 and does not exist in the array.
```

Apporach:
- Create all substring from s and check if the set size is 2^k or not

```cpp
bool hasAllCodes(string s, int k) {
  int n = s.size();
  if (k > n)
    return false;

  unordered_set<string> set;
  for (int i = 0; i <= n - k; i++) {
    set.insert(s.substr(i,k));
  }

  return set.size() == (1 << k);
}
```