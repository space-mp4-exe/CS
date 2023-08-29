#include <iostream>
using namespace std;

int main(){
	int x = 3, y = 5;

    void swap(int *a, int *b);
    swap(&x, &y);
    cout << x << y;

    return 0;
}

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}