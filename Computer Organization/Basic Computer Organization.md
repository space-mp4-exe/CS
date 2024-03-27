![[commonBusSystem.png]]
# Computer Registers
Computers use easily accessible registers to hold data within their cache.

| Register symbol | Number of bits | Resiter Name         | Function                     |
| --------------- | -------------- | -------------------- | ---------------------------- |
| DR              | 16             | Data register        | Holds memory operand         |
| AR              | 12             | Address register     | Holds address for memory     |
| AC              | 16             | Accumulator          | Processor register           |
| IR              | 16             | Instruction register | Holds instruction code       |
| PC              | 12             | Program counter      | Holds address of instruction |
| TR              | 16             | Temp register        | Holds temporary data         |
| INPR            | 8              | Input register       | Holds input character        |
| OUTR            | 8              | Output register      | Holds output character       |
A bus connects all of these registers together. Remember that only one of these registers can use the bus at one time. Each of the register are have control lines that connect to a control unit. For example, the TR has a load, increment, and clear control line. If a 1 comes from the control unit into the increment line, then the value of TR will be incremented. 
**Notes** 
- DR and AC are used for arithmetic operations
- any register can receive data from memory after a read, expect AR and INPR
- AR and PC are 12 bits because memory is 4096 words, which requires 12 bits to address to.
# Instructions
Memory-reference instruction - \[direct/ indirect address{1}]\[opcode{3}]\[Address{12}]
Register-reference instruction - \[0111]\[Register operation{12}]
IO-reference instruction - \[1111]\[IO operation{12}]

Lets say that you had hex code 013A, in binary this would be 0000 0001 0011 1010. You might be able to see the different parts of the code from the formatting above. 
```
|direct address | opcode |   address  |
        ^           ^          ^
|       0       |  000   |000100111010|
```
This means that you AND the value at the address from memory with the value already in the accumulator. We omit the value in the accumulator for these codes. 
Another instruction code could be 1234, binary 0001 0010 0011 0100. It's the same as the last instruction code. We can tell from the first bit that it has direct addressing. We can tell from the 2nd thru 4th bits that it wants us to add the value at the address with the value in the accumulator. The rest of the instructions act this way as well.

| symbol | Hexcode I=0/1 | Description                             |
| ------ | ------------- | --------------------------------------- |
| AND    | 0xxx/8xxx     | AND memory word to AC                   |
| ADD    | 1xxx/9xxx     | Add memory word to AC                   |
| LDA    | 2xxx/Axxx     | Load memory word to AC                  |
| STA    | 3xxx/Bxxx     | Store content of AC in memory           |
| BUN    | 4xxx/Cxxx     | Branch unconditionally                  |
| BSA    | 5xxx/Dxxx     | Branch and save return address          |
| ISZ    | 6xxx/Exxx     | Increment and skip if zero              |
| CLA    | 7800          | Clear AC                                |
| CLE    | 7400          | Clear E                                 |
| CMA    | 7200          | Complement AC                           |
| CME    | 7100          | Complement E                            |
| CIR    | 7080          | Circulate right AC and E                |
| CIL    | 7040          | Circulate left Ac and E                 |
| INC    | 7020          | Increment AC                            |
| SPA    | 7010          | Skip next instruction if AC is positive |
| INP    | F800          | Input character to AC                   |
| OUT    | F400          | Output character from AC                |
| SKI    | F200          | Skip on input flag                      |
| SKO    | F100          | Skip on output flag                     |
