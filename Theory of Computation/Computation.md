Three central areas of the theory of computation
- Automata
- Computability
- Complexity
## Complexity Theory
describes how complex it is to compute an answer to a problem [link](https://en.wikipedia.org/wiki/Computational_complexity_theory). So sorting a list of numbers is easy and scheduling things with some constraints is hard. 

## Languages
languages are a set of words and syntax we can use to make programs. 

**Regular Languages** - can be recognized by finite automata or regular expressions
**Context-free languages** - can be recognized by pushdown automata or context-free grammars. 
**Decidable languages** - have an algorithm that can determine membership of the language.
**Undecidable languages** - no algorithm that can determine membership of the language.

$\forall$: for all (*forall*)
$\exists$: there exists (*e/xi sts*)
$\exists!$: there exists a unique... 
$\implies$: implies (*=>*)
$\in$: is an element of. (*inn*)

## Finite Automata
Think of them as flow charts that can accept a string as an input. Each of the characters of the string are fed into the automata.

**Deterministic Finite Automata** are defined with this quintuple.
$(Q,\Sigma,\delta, q_{0}, F)$ 
$Q$ is the set of states, $\Sigma$ is the finite set of symbols called the input alphabet, $\delta: Q \times \Sigma \to Q$ is a total function called the transition function, $q_{0}\in Q$ is the initial state, $F\subseteq Q$ is a set of final states.   
## Nondeterminism

## Regular Expressions
**Regular language** - a language that is accepted by some finite automaton.
## Non-regular Languages
