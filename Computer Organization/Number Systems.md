The four number systems that we will use the most is **[Decimal](https://en.wikipedia.org/wiki/Decimal)**, **[Binary](https://en.wikipedia.org/wiki/Binary_number)**, **[Octal](https://en.wikipedia.org/wiki/Octal)**, and **[Hexadecimal](https://simple.wikipedia.org/wiki/Hexadecimal)**. 
# Converting
**Binary to Decimal** 
Multiply each bit by $2^n$, where $n$ is the "weight" of the bit and add the results.
*Ex*: 101011 = 43. 
$$\begin{split}
1 \times 2^0 &= 1 \\
1 \times 2^1 &= 2 \\
0 \times 2^2 &= 0 \\
1 \times 2^3 &= 8 \\
0 \times 2^4 &= 0 \\
1 \times 2^5 &= 32 \\
1 + 2 + 8 + 32 &= 43
\end{split}$$ **Octal to Decimal** 
This is the same as binary to decimal. Just multiply each bit by $8^n$, where $n$ is the "weight" of the bit and add the results.
*Ex*: 724 = 468
$$\begin{split}
4 \times 8^0 &= 4 \\
2 \times 8^1 &= 16 \\
7 \times 8^2 &= 448 \\
4+16+448 &= 468
\end{split}$$ **Hexadecimal to Decimal**
This is the same as binary to decimal. Just multiply each bit by $16^n$, where $n$ is the "weight" of the bit and add the results.
*Ex*: ABC = 2748
$$\begin{split}
C \times 16^0 = 12 \times 1 &= 12 \\
B \times 16^1 = 11 \times 16 &= 176\\
A \times16^2 = 10 \times 256 &= 2560 \\
12 +176+ 2560 &= 2748
\end{split}$$ **Decimal to Binary**
divide by 2 while keeping track of the remainder. The remainder becomes the digits of the number.
*Ex*: 125 = 1111101
$$\begin{split}
2 \overline{)125}\\
2 \overline{)62},R = 1\\
2 \overline{)31} ,R = 0\\
2 \overline{)15} ,R = 1\\
2 \overline{)7} ,R = 1\\
2 \overline{)3} ,R = 1\\
2 \overline{)1} ,R = 1\\
0,R = 1
\end{split}$$ 
# Gray Code
[wiki](https://en.wikipedia.org/wiki/Gray_code) It is a way of writing binary code where only 1 bit is allowed to change when incremented.

# Fixed Point Numbers
We use a 0 to represent positive numbers and 1 to represent negative numbers. 
**2s Complement** - Take the complement of a binary number (*eg*. 6 = 0000 0110 -> 1111 1001) and add 1 to it (*eg*. 1111 1001 + 1 = 1111 1010 = -6). Use this to find a negative of a fixed point number.
We do this to subtract numbers so that we would only need an addition unit in the computer. 

**Overflow** - if the sum of 2 n-bit numbers requires n+1 bits, then an overflow has occurred. If the `XOR` $\oplus$ of the "carry-in" and the "carry-out" of the sign bit is 1, then there was an overflow.
*Ex*: 70 + 80 = 0100 0110 + 0101 0000 = 1001 0110. 1001 0110 is -106, which is obviously wrong, you can't get a negative numbers when you add two positive numbers. 
$$
\begin{split}
0100 \:0110 \\ 
+0101 \:0000 \\
\hline 
1001 \:0110
\end{split}
$$**Mantissa** - This is a signed magnitude number where S is the sign bit
$$
\begin{flalign}
N = 1.5 = 1.1_{2} = (1.1)2^0\\
N = (-1)^{S}2^{E-127}(1.M)\\
\rightarrow E - 127 = 0
\end{flalign}
$$ The range of 32-bit floating point numbers are -127 to 127.