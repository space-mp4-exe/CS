#include <iostream>
#include <vector>
using namespace std;

int main(){
	int *p = new int[2];

	p[0] = 4;
	p[1] = 5;

	cout << p[0] << endl;

	cout << p[1] << endl;

	p = new int[4];
	
	cout << p[0] << endl;

	delete []p;
}
