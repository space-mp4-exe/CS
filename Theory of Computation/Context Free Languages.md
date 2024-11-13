# Context Free Language
These languages are a step above regular languages in Chomsky's hierarchy of languages. We can recognize a context free language with a push down automata. 
production rules are in the form of:
$$
\begin{split}
S \to AB \\ 
A \to aaA \\
A \to \lambda \\
B \to Bb \\
B \to \lambda
\end{split}
$$
These specific rules make the language $L(G)=\{ a^{2n}b^m : n \geq 0, m \geq0 \}$. We can use these rules to create a *derivation tree*, which is a graph where the root is the starting symbol with the results of the rules underneath. 
# Parsing and Ambiguity
*parsing* - describes finding a sequence of productions by which a $w\in L(G)$ is derived. Basically finding a string that is in the language.
A context-free grammar $G$ is said to be **ambiguous** if there exists some $w\in L(G)$ that has at least two distinct derivation trees. For any $w\in L(G)$, we can create a derivation tree. There is the possibility that more than one tree can be produced from the same $w$.
# Simplification
A way to simplify context free grammars is to put them into forms that are easier to analyze. We can put production rules into *normal forms* like *Chomsky normal form*. One