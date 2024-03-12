Data is stored in variables, or registers. 
Computers can't do things like `x = a*b` in one step, they first have to divide it into very small operations called mircrooperations. 
Each microoperation is represented with a $\leftarrow$. So an operation would look like `R <- A`, this operation would transfer the contents of register `A` to register `R`. 
# Bus
Computers use a bus to transfer data in between registers. They use a bus to limit the number of connections in between registers. In the `R <- A` example, there would have to be a dedicated line between `R` and `A`. The data actually goes thru the bus before arriving at `R`, so you could write the operation as `BUS <- A` and `R <- BUS`.