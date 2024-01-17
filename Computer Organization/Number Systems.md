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
\end{split}$$**Octal to Decimal** 
This is the same as binary to decimal. Just multiply each bit by $8^n$, where $n$ is the "weight" of the bit and add the results.
*Ex*: 724 = 468
$$\begin{split}
4 \times 8^0 &= 4 \\
2 \times 8^1 &= 16 \\
7 \times 8^2 &= 448 \\
4+16+448 &= 468
\end{split}$$**Hexadecimal to Decimal**
This is the same as binary to decimal. Just multiply each bit by $16^n$, where $n$ is the "weight" of the bit and add the results.
*Ex*: ABC = 2748
$$\begin{split}
C \times 16^0 = 12 \times 1 &= 12 \\
B \times 16^1 = 11 \times 16 &= 176\\
A \times16^2 = 10 \times 256 &= 2560 \\
12 +176+ 2560 &= 2748
\end{split}$$**Decimal to Binary**
