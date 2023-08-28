**Null pointers** - pointers that point to a null object. `int* p1 = NULL;` 
If a pointer is null, you shouldn't be pulling data from it. 

```C++
int* p = NULL;

if(p != NULL){
	cout << *p << '\n';
}
else {
	cout << "A null pointer" << '\n';
}
``` 

we can also declare a pointer of a pointer. 

```C++
int x = 5;
int* p = &x;
int** pp = &p;
```

`*p` cannot be assigned to `pp` because `pp` expects to be assigned a pointer, not an integer.
