**Pipe** ways of communicating between processes. 
 - Ordinary pipes: cannot be accessed from outside the process that created it. Typically a parent processes creates a pipe and uses to communicate with a child process.
 - Named pipes: can be accessed with a parent-child relationship
Ordinary pipes
	Both parent and child close one half of the pipe so there is only one reader or writer. Ordinary pipes follow a producer-consumer style. one process is the producer and the other is the consumer. Implemented in the kernel.
Named pipes
	