## Bit Hacks

[reference](https://graphics.stanford.edu/~seander/bithacks.html)
```c
x = 0xb011011000
~x = 0xb100100111
-x = 0xb100101000
```
```c
x = ~x + 1
-x = -x + 1
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