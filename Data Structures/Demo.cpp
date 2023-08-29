#include <iostream>
using namespace std;

int main(){
	int x = 5;
	int y = 3;

	int add(int* a, int* b);
	int z = add(&x, &y);

	cout << z;
}

int add(int* a, int* b){
	return *a + *b;
}
