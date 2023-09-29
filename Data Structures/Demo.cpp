#include <iostream>
#include <list>
using namespace std;

void printRightSide(int arr[]){
	int mid;
	int arrSize = sizeof(arr)/sizeof(arr[0]);
	mid = arrSize/ 2;
	//cout << arr[mid] << endl;
	if(arr[mid] < 5){
        int *rightSide = new int(mid);
        for(int i = 0; i < arrSize / 2; i++){
            rightSide[i] = arr[i + mid + 1];
        }
		cout << rightSide[0] << rightSide[1] << rightSide[2] << endl;
    }
}

int main(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	printRightSide(arr);
}