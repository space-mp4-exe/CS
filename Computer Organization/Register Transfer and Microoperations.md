Data is stored in variables, or registers. 
Computers can't do things like `x = a*b` in one step, they first have to divide it into very small operations called mircrooperations. 
Each microoperation is represented with a $\leftarrow$. So an operation would look like `R <- A`, this operation would transfer the contents of register `A` to register `R`. 
# Bus
Computers use a bus to transfer data in between registers. They use a bus to limit the number of connections in between registers. In the `R <- A` example, there would have to be a dedicated line between `R` and `A`. The data actually goes thru the bus before arriving at `R`, so you could write the operation as `BUS <- A` and `R <- BUS`.

# Microoperations
| symoblic representation | description |
| ---- | ---- |
| R3 $\leftarrow$ R1 + R2 | R1 and R2 are added and put into R3 |
| R3 $\leftarrow$ R1 - R2 | R1 and R2 are subtracted and put into R3 |
| R2 $\leftarrow \bar{R2}$ | The complement of R2 is stored in R2 (1's complement) |
| R2 $\leftarrow \bar{R2}$ + 1 | The complement plus 1 of R2 is stored in R2 (negation) |
| R3 $\leftarrow \bar{R2}$ + 1 + R1 | R1 plus the 2's complement of R2 (subtraction) |
| R1 $\leftarrow$ R1 + 1 | increment R1 |
| R1 $\leftarrow$ R1 - 1 | decrement R1 |

Shifts operations 

| symbolic representation | description |
| ---- | ---- |
| R $\leftarrow$ shl R | Shift-left register R |
| R $\leftarrow$ shr R | Shift-right register R |
| R $\leftarrow$ cil R | Circular shift-left register R |
| R $\leftarrow$ cir R | Circular shift-left register R |
| R $\leftarrow$ ashl R | Arithmetic shift-left register R |
| R $\leftarrow$ ashr R | Arithmetic shift-left register R |
