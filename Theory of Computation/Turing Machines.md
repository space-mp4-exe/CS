# Turing Machines
These are similar to the other finite automata that we've seen. There is a tape with unlimited memory, it has accept and reject states. If it doesn't stop at a reject or accept state, then it will continue running forever. The machine can write and read the tape, it can move the tape to the left and to the right.
Definition: ($Q,\Sigma,\Gamma,\delta,q_{0},q_{accept},q_{reject}$)
- $Q$ is the set of states
- $\Sigma$ is the input alphabet not containing the blank symbol
- $\Gamma$ is the tape alphabet, where $\_ \in \Gamma$ and $\Sigma \subseteq \Gamma$
- $\delta:Q\times\Gamma\to Q\times\Gamma \times\{L,R\}$ is the transition function
- $q_{0}\in Q$ is the start state
- $q_{accept}\in Q$ is the accept state 
- $q_{reject} \in Q$ is the reject state


**Configuration** 
- current state
- current tape contents
- current head location
$uqv$: head is at leftmost symbol in $v(u, v \in \Gamma^*)$. 
*Ex*: 1011 $q_{0}$ 01111 represent tape contents of 101101111 with the head currently over the second 0. 
We say that a configuration $C_{1}$ **yields** configuration $C_{2}$ if the turning machine $M$ can legally go from $C_{1}$ to $C_{2}$ in a single step. 

*Ex*: Let $A=\{ 0^{2^n} | n \geq 0\}$, the language consisting of all strings of 0s whose length is a power of 2. 
We can find a Turing machine by writing the string of zeros on the tape followed by a # and with a count after it. We would then read the first 0, mark that spot with an x, move all the way to the count, increment it, then move all the way back until we see an x then mark the next 0 with an x. We repeat these steps until we mark the whole string of zeros with x's. At the end of the algorithm, we should have a string of x's followed by a # which is followed by a count of how many zeros there were. 
# Variants
# Definition of Algorithm