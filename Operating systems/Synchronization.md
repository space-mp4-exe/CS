# Background
Processes can run concurrently. Concurrent access to data an result in inconsistency. We have to use certain mechanisms to maintain consistency. 
Producer-consumer buffers: Producers and consumers both have access to the variables in the buffer.

Producer
```C
while (true) {  
	/* produce an item in next produced */  
	while (counter == BUFFER_SIZE) ;  
		/* do nothing */  
		buffer[in] = next_produced;  
		in = (in + 1) % BUFFER_SIZE;  
		counter++;  
}
```

Consumer
```C
while (true) {  
	while (counter == 0)  
		; /* do nothing */  
		next_consumed = buffer[out];  
		out = (out + 1) % BUFFER_SIZE;  
		counter--;  
		/* consume the item in next consumed */  
}
```

Race conditions are when these try to access same variable at the same time. 
# Critical - Section Problem
Consider a system of $n$ processes. Each of these processes has a segment of code called the **critical section**. No other processes can be in its critical process while another is also in its critical process. These are things like changing shared memory, reading or writing a file, etc. 

***Critical Section Problem*** - design a protocol for enforcing interaction and execution of non-overlapping critical sections.

An approach to this problem would for each process to *request* to enter it's critical section, it would then execute it, then it would exit. 
# Mutex Locks
# Semaphores
