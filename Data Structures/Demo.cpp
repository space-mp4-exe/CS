#include <iostream>
using namespace std;

int main(){
	int x = 5;
	int *p = &x;
	int **pp = &p;

	cout << p << endl;

	p++;

	cout << p << endl;
	cout << *pp;
}
