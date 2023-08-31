# Sets
- $Q = \{a/b | a \in Z \land b \in Z^+\}$

## Subsets
- $A \subseteq B$ "A is a subset of B"
- $A \subseteq B$ if and only if every element of A is also an element of B -> $A \subseteq B \iff \forall$ 

$(A \subseteq B) \land (B \subseteq C) \Rightarrow A \subseteq C$. This means that that $A$ is a sub set of $B$, which means that all of the values in $A$ are contained within $B$. The second part means that $B$ is also a subset of $C$, since that $A$ is a subset of $B$ and $B$ is a subset of $C$ that means that $A$ is a subset of $C$! You can visualize this with a venn diagram.

**Proper subsets** 
$A \subset B$ 
$A \subset B \iff \forall x (x \in A \rightarrow x \in B) \land \neg \forall x(x\in B \rightarrow x \in A)$ 

**Cardinality of sets** - if a set $S$ contains n distinct elements, $n \in N$, we call $S$ a *finite set* with *cardinality n*. 
- ex: A = {Mercedes, BMW, Porsche}, |A| = 3
- $D = \{x \in N | x <= 7000\}$                      $|D| = 7001$  
Cardinality doesn't say anything about the contents of a set

**Cartesian Product** - $A \times B = \{(a, b) | a \in A \land b\in B\}$ 
$A = \{x, y\}$, $B = \{a, b, c\}$ -> $A\times B = \{(x,a), (x,b), (x,c), (y,a), (y,b), (y,c)\}$ 
sort of like a [dot product](https://en.wikipedia.org/wiki/Dot_product). 

how can we prove $A \cup(B\cap C) = (A\cup B)\cap (A \cup C)$ 
