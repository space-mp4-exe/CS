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
We say $R$ is a **regular expression** if $R$ is 
- $a$ for some $a\in\Sigma$ 
- $\lambda$
- $\emptyset$
- ($R_{1}+R_{2}$)
- ($R_{1}\circ R_{2}$),where $R_{1}$ and $R_{2}$ are regular expressions
- ($R_{1}*$)
$L(R)$ is the language of a regular expression $R$.
$R+\emptyset=R$, $R\circ\lambda =R$. $R+\lambda\neq R$, if $R=0$, then $L(R)=\{ 0 \}$ but $L(R+\lambda)=\{ \lambda,0 \}$. $R\circ\emptyset\neq R$, because if we concatenate something with nothing, we get nothing.
A language is regular if and only if some regular expression describes it. 
![[DFA examples.webp|465]] 
## Non-regular Languages
An example of a non regular language would be $C=0^n1^n$, where $n$ some random number. If $n$ was defined as a specific number, then it would be regular. $L=0^*1^*$ is regular. $C$ is not regular because it seems to need to remember how many 0s there were to match it to the number of 1s. 
## Pumping Lemma for Regular Languages
- All regular languages have a special property. All strings in the language can be "pumped" if they are at least as long as a certain special value, called the *pumping length*.

If $A$ is a regular language, then there is a number $p$ (the pumping length) where, if $s$ is any string in $A$ of length at least $p$, then $s$ may be divided in three parts 
$$
s = xyz
$$ such that 
- $\forall i \in \{ 0,1,2,\dots \}$, it holds that $xyz\in A$
- $|y|>0$
- $|xy|\leq p$
Languages can be split into those three parts. The part before the pumping, the part to be pumped, and the final accept state. The pumping part has to happen in the first $p$ characters. 

**Ex** - $B =\{0^n 1^n|n\geq 0\}$ show that $B$ is not regular. Lets use proof by contradiction using pumping lemma. The pumping length is $p$. We can use $p$ to make $s=0^p 1^p$. $s \in B$ and $|s|=2p\geq p$, so we can apply the pumping lemma. 
We can tell from the third rule that $|xy|\leq p$, therefore $x =0^k, y=0^l$ and $k +l=p,l\geq 0$. Pumping lemma states then that we should be able to repeat the 0s as many times as we want and still be in $B$, but since there has to be as many 1s as 0s, $B$ isn't regular. 
$s'=xyyz$ should belong to $B$, however $s'=0^k 0^l 0^l z$. We have $k+l+l+p-l-k$ number of 0s, which simplifies to $p+l$ 0s where $l$ is bigger than 1. We also have $p$ number of 1s. So we have a different number of 0s from 1s. 

Lemma is hard man, its all so abstract and the solutions for each language are so different from each other. 
