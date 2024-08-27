An operating system is the program that acts as an intermediary for the hardware and the user. Its a collection of programs that manages the hardware, allocates memory for programs, manages the timing of program computation, and other services for user and hardware. 

## Kernel
The program that is running at all times is the [**kernel**](https://en.wikipedia.org/wiki/Kernel_(operating_system)). Kernels are always in memory, protected from the user and other programs. It handles interrupts and manages the hardware, like hard drive memory allocation. Programs in user space cannot directly interact with the kernel, they must first make system call which is usually a wrapper function.  

## Cores
The OS has access to CPU and its computation cores. Cores are the actual hardware that runs programs. A core can only compute one program at a time, but they can change the program they are running. So a core can have only one thread running at a time, but multiple threads running over a couple of seconds. 

## Interrupts
Interrupts are used to transfer control from the currently executing program to the appropriate interrupts service routine. This is how the OS controls the scheduling of programs.  A *trap* or *exception* is a software-generated interrupt caused by an error or a user program. 

