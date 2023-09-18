# Algorithms
**Linear Search** - going one by one down the list and checking if they are the same
**Binary Search** - going to the middle and changing mid-point based on results
**Problems**, you have to search the list to find something

# Direct Address Table (DAT)
**DAT** is also a linear data structure. Stores an object an object in a position in an array that can be directly referenced by the address of the object
**Limitation**, DAT does not make efficient use of memory if a single key value is way bigger than  the number of objects. There would be a large gap in the array. 

# Hash Table
Hash table improves the time-space trade-off of DAT by introducing an extra step "hashing". 
**Collision** - when an element has the same hash, trying to add multiple elements to one array entry. Sometimes Collisions are impossible to avoid, like if we expect to add new objects generated from an unknown distribution in the future. 
**Solutions to Collisions**:
- **Separate Chaining**- put collided objects on a list accessible through the target cell.
- **Open Addressing**- look for an empty cell on table to add the element to.

**Separate chaining** -
- Hold the first object in the hash table. 
	- This saves the space of an accessor but may sacrifice some other things.
- Only hold some accessor to the list in the hash table.
	- Cost extra space for the accessor, but more flexible.

```c++
class HashTable {
private:
	int size;
	int hash(int key);
	Node** table;
public:
	void CreateTable(/*arg*/);
	Node* search(int key);
	void add(Node* temp);
	void remove(int key);
	HashTable();
	void PrintTable();
}
```

