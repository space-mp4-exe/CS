# Dynamic Memory Allocation
```c++
int* p;

p = new int;

*p = 5;

p++;
```
The phrase "new int" allocates a memory chunk whose size can shrink and grow throughout the time of the program. You can use `delete` to free the memory space. 

works for arrays 
```c++
int size;
cin >> size;
int* p = new int[size];
cout << *p;
``` 

# Vectors
put `inclue <vector>` in the header. 
syntax
```c++
#include <vector>
int main(){
	vector<int> x(2); //<- declaration, initializes to 0s
	x.at(0) = 5;
	x[0] = 3;
	cout << x.at(1);
}
```

**Iterator**
```c++
vector<int> x={1, 2, 3, 4, 5};
vector<int>::iterator iter;
iter = x.begin(); //assigns the iterator to the first address of 'x'
iter++;
cout << *iter; //<- prints 2
cout << *(iter + 2); //<-prints 4
```

**Insert and Erase**
```c++
vector<int> x = {1, 2, 3};
vector<int>::iterator iter;
iter = x.begin();
x.insert(iter+1, 10); //vector is now {1, 10, 2, 3}

iter = x.begin();
x.erase(iter+1); //vector is now {1, 2, 3}
```
