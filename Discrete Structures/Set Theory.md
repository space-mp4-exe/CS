# Sets
**Set** - Unordered collection of elements
- $A \in B$ "$A$ is an element of $B$", "$A$ is a member of $B$"
- $A\not\in B$ "$A$ is not an element of $B$"
**Standard Sets** 
- Natural Numbers $\mathbb{N} = \{0, 1, 2\}$ 
- Integers $\mathbb{Z} = \{-2, -1, 0, 1\}$
- Real Numbers $\mathbb{R} = \{0, 1, 2, \pi\}$ 
**Examples**
- $A = \{x\mid P(x)\}$ "Set of all $x$ such that $P(x)$"
- $A = \{x\mid x\in N \land x > 7\} = \{8, 9, 10\}$ set builder notation
- $Q = \{a/b | a \in Z \land b \in Z^+\}$ set of rational numbers

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

## Set Operations
- **Union**($\cup$) - $A\cup B = \{x\mid x\in A \lor x\in B\}$ 
	- **EX**: If $A = \{1, 2, 3\}$, $B = \{4, 5, 6\}$ then $A\cup B =\{1, 2, 3, 4, 5, 6\}$ 
- **Intersection**($\cap$) - $A \cap B = \{x\mid x\in A \land x\in B\}$ 
	- **EX**: if $A = \{1, 2, 3\}$ and $B = \{2, 3, 4\}$ then $A\cap B = \{2, 3\}$ 

how can we prove $A \cup(B\cap C) = (A\cup B)\cap (A \cup C)$ 
