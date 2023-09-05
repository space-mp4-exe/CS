//
// ========================================
// HW3: Implement a Vector Class
// ========================================
// 
// In this assignment, we will implement 
// a vector class based on array, pointer 
// and dynamic memory allocation. 
// 
// The class has two private member 
// variables and some member functions. 
// Their designs are explained below. 
// 
// You can add new member functions 
// but not new member variables. In 
// addition, you cannot use any existing 
// vector-related library or function. 
// 
// 


#include <iostream>
using namespace std;

// 
// ======= Task =======
// Design and implement all member 
// functions of the MyVector class. 
// 
class MyVector {

public:

	// The "vsize" function returns the size 
	// of the current vector.  
	int vsize();

	// The "empty" function returns 1 if the 
	// current vector has no element and 0 otherwise. 
	int empty();

	// The "at" function returns the idx_th element 
	// of the vector. It also returns -1 if "idx" 
	// is outside the range of the current vector.
	int at(int idx);

	// The "resize" function resizes the current 
	// vector into a vector of size n. Note there 
	// are two scenarios (in lecture slides) which 
	// may need to be addressed separately. 
	void resize(int n);

	// The "push_back" function adds a new element 
	// "x" to the end of the current vector. Note 
	// the vector size increases after addition. 
	void push_back(int x);

	// The "pop_back" function removes the last 
	// element from the current vector, but does 
	// nothing if the current vector is empty. 
	// Note the vector size decreases after pop. 
	void pop_back();

	// The "insert" function inserts a new element 
	// "x" as the idx_th element in the current vector.
	// It also does nothing if "idx" is outside the 
	// range of the current vector. 
	void insert(int idx, int x);

	// The "erase" function removes the idx_th element 
	// from the vector. It also does nothing if the 
	// current vector is empty or if "idx" is outside 
	// the range of the current vector. 
	void erase(int idx);

	// The constructor should initialize 
	// pointer "p" to NULL and "size" to 0. 
	MyVector();

private:

	int* p; // This pointer holds the vector (or,essentially, 
	// address of an array that holds the vector elements.)
	// Do remember to update it after some vector operations.

	int size; // This integer holds the size of the current 
	// vector. Do remember to update it after some 
	// vector operations. 
};


// The main function has been completed for you. 
// It is used to test your implmentation. 
// You should not modify it (unless there is typo).
int main()
{
	MyVector x;

	int mode;
	int new_size, idx, data;
	int temp;

	cin >> mode; // This decides which function to test. 
	cin >> new_size >> idx >> data;

	// Mode 0: test push_back(), vsize() and at()
	if (mode == 0) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 1: test resize()
	else if (mode == 1)
	{
		while (cin >> temp) {
			x.push_back(temp);
		}

		x.resize(new_size);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 2: test pop_back()
	else if (mode == 2) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.pop_back();

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 3: test insert()
	else if (mode == 3) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.insert(idx, data);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 4: test erase()
	else if (mode == 4) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.erase(idx);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	else {
		cout << "Wrong Mode Input!";
	}

	return 0;
}
