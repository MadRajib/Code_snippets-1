## Bit Hacks

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
