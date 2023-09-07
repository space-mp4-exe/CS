# Linked List
Data in a linked list is stored in a `node` which are connected by `links`. each of the links are point to the next node in the list. Because each node has a link pointing to it, the nodes can be anywhere in memory. 
- **Singly Linked List** - nodes are connected one by one through directional links
- **Doubly Linked List** - Nodes are connected one by one with bidirectional links
- **Circular Linked List** - same as a singly linked list, but with a pointer from the last node to the first one
**Traverse** - travel from head to tail. 
C++ has `std::list` 
```C++
#include <list>

int main(){
	list<int> x;
	x.push_front(4); //add node to head
	x.push_back(6); //add node to tail

	cout << x.size();//return list size
	cout << x.front();//return list head
	cout << x.back();//return list tail. 
}
```
use `iterator` to access the nodes
```c++
list<int>:: iterator it;
for(it=x.begin(); it != x.end(); it++){
	cout << *it;
}
```
`.begin()` - returns address of the first node
`.end()` - returns the address of the last node

