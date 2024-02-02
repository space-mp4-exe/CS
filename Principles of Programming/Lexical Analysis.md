The first step in compiling a program is lexical analysis. The first step it taking the source code and translating each "word" into a token. It will take each symbol of the code, like ";", "`int x = 5`" and change them into standardized tokens. "`for`" $\rightarrow$ KEYWORD_FOR. "`(`" $\rightarrow$ LEFT_PAR. 

Scanner generators, like flex, take regular expressions and produce compilable code. Regular expressions serve as rules to comb through a piece of code to organize and label all the tokens. [video](https://www.youtube.com/watch?v=LpVufkH4gog) 
# Deterministic Finite Automaton ([DFA](https://en.wikipedia.org/wiki/Deterministic_finite_automaton))
These things are used for pattern finding in code. They use a series of nodes that are connected to each other with input and output labels. So if we where at node $S_0$ and our input happened to be 1, then we would follow our output label over to node $S_1$. [video](https://www.youtube.com/watch?v=40i4PKpM0cI) 

**Nondeterministic Finite Automaton** - The difference between a NFA and a DFA is that a NFA could have multiple of the same label going to different nodes, so the same input can lead to different outputs. this is problematic for lexical scanners. 

**Epsilons ($\epsilon$)** act as a sort of wildcard for DFA diagrams. They don't take in input strings to travel across the label. ![[Screenshot 2024-02-02 at 1.01.52 PM.png]]Using epsilon labels to loop the DFA on itself to represent the $*$. 
![[Screenshot 2024-02-02 at 1.02.45 PM.png]]As you see in the above picture, we can use epsilon labels to represent $a \mid b$. 