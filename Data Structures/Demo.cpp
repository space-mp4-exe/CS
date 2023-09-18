#include <iostream>
#include <list>
using namespace std;

int main(){
	int SumF(int n);
	cout << SumF(20);
}

int SumF(int n){
	if(n == 1){
		return n;
	}
	else {
		return n + SumF(n/2);
	}
}
