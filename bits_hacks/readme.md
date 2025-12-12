## Bit Hacks

[reference](https://graphics.stanford.edu/~seander/bithacks.html)

```c
// count trailing zeros (GCC/Clang)
    int tz = __builtin_ctz(n);
```

```c
x = 0xb011011000
~x = 0xb100100111
-x = 0xb100101000
```
```c
// since we have
x + ~x = -1;
-x = ~x + 1;
```
#### set kth bith in a word x to 1.
```c
y = x | (1 << k)
```

#### clear the kth bit in a word x.
```c
y = x & ~(1 << k)
```

#### toggle the kth bit
```c
y = x ^ (1 << k)
```

#### Remove the last set bit
```c
x = x & (x - 1)
```
#### Compute the mask of the least-significant ! in word ".
```c
r = x & (-x);
// 
```

#### extract a bit field from a word x
#### mask and shift
```c
(x & mask) >> shift
```

#### set a bit field in word x to a valye y.
#### invert mask to clear, and OR the shifted value.
```c
x = (x & ~mask) | ((y << shift) & mask)
```

#### swap two integers
```c
x = x ^ y
y = x ^ y
x = x ^ y
```
-> poor at explotiting intruction level parallelism (ILP)

#### Min of two integers
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

#### Modular Addition
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

#### Round up to a Power of 2
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

#### Counting bits set (naive way)

```c
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v

for (c = 0; v; v >>= 1)
{
  c += v & 1;
}
```
The naive approach requires one iteration per bit, until no more bits are set. So on a 32-bit word with only the high set, it will go through 32 iterations.

#### Counting bits set, Brian Kernighan's way
```c
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v
for (c = 0; v; c++)
{
  v &= v - 1; // clear the least significant bit set
}
```

#### Check if a no is power of 2
```c
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
#### Check for Power of 8
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
#### Find Xor of a number without using XOR operator:
```c
x ^ y = x~y + ~xy
```

#### Add 1 to an interger without using +, -, /, ++, --
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

#### Odd or even
```c
return (x & 1)? false: true;

return ((x >> 1) << 1) ==  x
```

#### Count the consecutive zero bits (trailing) on the right linearly
```c
unsigned int v;  // input to count trailing zero bits
int c;  // output: c will count v's trailing zero bits,
        // so if v is 1101000 (base 2), then c will be 3

v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
for (c = 0; v; c++)
  v >>= 1;

```
