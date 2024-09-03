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

[**Deterministic Finite Automata**](https://en.wikipedia.org/wiki/Deterministic_finite_automaton) are defined with this quintuple.
$(Q,\Sigma,\delta, q_{0}, F)$ 
$Q$ is the set of states, $\Sigma$ is the finite set of symbols called the input alphabet, $\delta: Q \times \Sigma \to Q$ is a total function called the transition function, $q_{0}\in Q$ is the initial state, $F\subseteq Q$ is a set of final states.   
## Nondeterminism
[Nondeterministic finite automaton](https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton)
![[Pasted image 20240903124141.png]] 
This Automata is non-determinist because it "guesses" when the string ends. Notice how $q_{0}$ has two $a$ variables pointing outwards from it. 
The quintuple for this automata is $Q=\{q_{0},q_{1},q_{2}\}$, $\Sigma=\{a,b\}$, $\delta$ is this table, $q_{0}=\{q_{0}\}$, $F=\{q_{2}\}$.

| Q       | a                 | b           | $\lambda$   |
| ------- | ----------------- | ----------- | ----------- |
| $q_{0}$ | {$q_{0}$,$q_{1}$} | {$q_{0}$}   | $\emptyset$ |
| $q_{1}$ | $\emptyset$       | {$q_{2}$}   | $\emptyset$ |
| $q_{2}$ | $\emptyset$       | $\emptyset$ | $\emptyset$ |
## Regular Expressions
**Regular language** - a language that is accepted by some finite automaton.
## Non-regular Languages
