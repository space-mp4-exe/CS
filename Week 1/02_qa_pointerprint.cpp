#include <iostream>

using namespace std;

int main()
{
	int x = 5;
	int *ptr = &x;

	cout << ptr;

	ptr++;

	cout << ptr;

	return 0;
}
