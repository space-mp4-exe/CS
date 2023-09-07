#include <iostream>
#include <vector>
using namespace std;

int main(){
	int *p = new int[2];
	int *q = new int[2];

	p[0] = 4;
	p[1] = 5;

	q[0] = 2;
	q[1] = 3;

	p[0] = q[0];
	p[1] = q[1];

	cout << p[0] << endl;

	cout << p[1] << endl;

	delete []p;
	delete []q;
}
