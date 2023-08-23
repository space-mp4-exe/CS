If we have code `cin >> x[0] >> x[1]` and we want to assign 3 to `x[0]` and 5 to `x[1]` we have to type 3, a space, and then a 5.

**Pointer** - a special type of variable that hold an address to a variable.

```
int x = 5;
int* ptr; <- declare pointer
ptr = &x; <- Extract address of variable "x"
```

access data through pointer
```
int x = 5;
int *ptr = &x;

cout << *ptr;

*ptr = 2; <- assigns "2" to the memory chunk at "ptr"
```

Access one class object through pointer
```
Student x;
Strudent *ptr = &x;

ptr->set_SID(30); <- "ptr" is a pointer, so use "->"
ptr->print_SID();

x.set_SID(30);
x.print_SID();
```

