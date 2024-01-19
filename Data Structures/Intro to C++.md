```Cpp
#include <iostream>

int main()
{
	int x;

	std::cin >> x;

	std::cout << x;

	return 0;
}
```

the header is assumed to include 
```C++
#include <iostream>

using namespace std;
```

You can initialize multiple variables in one line with commas.
`int x, y = 5;`   
`endl` is basically  `/n`.

You have to declare a function before it is called if the function is below the parent function that it is called in. We have to declare `Sum` because it is defined after `main`.
```C++
int main()
{
	int x=1, y=2, z;
	int Sum(int a, int b);
	z = Sum(x, y);
	return 0;
}
int Sum(int a, int b)
{
	int z;
	z = a + b;
	return z;
}
```

**Destructor**: deletes classes. used to free dynamically allocated memory.