A combinational circuit that performs addition of two bits is called a *half adder*.
# Flip Flop Gates
**SR** 
excitation table

| start | end | S | R |
| ---- | ---- | ---- | ---- |
| 0 | 0 | 0 | x |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 0 | 1 |
| 1 | 1 | x | 0 |
JK 
excitation table 

| start | end | J | K |
| ---- | ---- | ---- | ---- |
| 0 | 0 | 0 | x |
| 0 | 1 | 1 | x |
| 1 | 0 | x | 1 |
| 1 | 1 | x | 0 |
# Registers
We can use flip flops to create [registers](https://en.wikipedia.org/wiki/Processor_register), these are basically is very quickly accessible data inside a CPU. The data is called a "word". The length of each word is determined by the type of CPU. If it is a 32-bit CPU, then each word, each register, is 32 bits long. If it is 64-bit, then they are 64 bits long. 
Data is loaded from RAM into these registers to have operations ([arithmetic operations](https://en.wikipedia.org/wiki/Arithmetic_operation "Arithmetic operation"), [bitwise operations](https://en.wikipedia.org/wiki/Bitwise_operation "Bitwise operation")) done on them (think about the [LDA](https://www.c64-wiki.com/wiki/LDA) instruction in assembly).
