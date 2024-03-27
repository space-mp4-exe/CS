A combinational circuit that performs addition of two bits is called a *half adder*.
# Flip Flop Gates
**SR** 
excitation table

| start | end | S   | R   |
| ----- | --- | --- | --- |
| 0     | 0   | 0   | x   |
| 0     | 1   | 1   | 0   |
| 1     | 0   | 0   | 1   |
| 1     | 1   | x   | 0   |

From what you can see from the table, you cannot have a 11 as the input.
JK 
excitation table 

| start | end | J   | K   |
| ----- | --- | --- | --- |
| 0     | 0   | 0   | x   |
| 0     | 1   | 1   | x   |
| 1     | 0   | x   | 1   |
| 1     | 1   | x   | 0   |

From you can see from the excitation table, JK flip flops are the same as SR flip flops, they just take the complement when the inputs are 11. 
# Registers
We can use flip flops to create [registers](https://en.wikipedia.org/wiki/Processor_register), these are basically is very quickly accessible data inside a CPU. The data is called a "word". The length of each word is determined by the type of CPU. If it is a 32-bit CPU, then each word, each register, is 32 bits long. If it is 64-bit, then they are 64 bits long. 
Data is loaded from RAM into these registers to have operations ([arithmetic operations](https://en.wikipedia.org/wiki/Arithmetic_operation "Arithmetic operation"), [bitwise operations](https://en.wikipedia.org/wiki/Bitwise_operation "Bitwise operation")) done on them (think about the [LDA](https://www.c64-wiki.com/wiki/LDA) instruction in assembly).
# Multiplexers and ROMs

[Multiplexers](https://en.wikipedia.org/wiki/Multiplexer) are circuits that take multiple inputs and combine them into a single data stream. A complementary "demultiplexer" will take this single data output and split it back into the multiple outputs. They have an $n$ number of inputs, with a $log_2(n)$ selector inputs. Input from the selector pins is taken and what is outputted is what is in the corresponding input pin. 
So if we had a 4:1 mux (a mux that has 4 input and 2 selector pins) and 01 was inputed to the selector pins (0 to $S_0$ and 1 to $S_1$) then the second input pin would be selected (pins are numbered in binary 0-3). Now, whatever is inputted into pin 01 will be the output.

[ROMs](https://en.wikipedia.org/wiki/Read-only_memory) act the same as muxes, but their contents are set-in-stone. If in entry at 01 is a 1, there will always be a 1 there. You cannot change the contents of a ROM, that's why it's read-only. 