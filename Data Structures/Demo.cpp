#include <iostream>
#include <list>
using namespace std;

<<<<<<< HEAD
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
=======
int main(){
	cout << "hi" << endl;
>>>>>>> 5af38a3 (changed something)
}

int main(){
	// Dynamically creating the array
    // of size = 5
    int* p = new int[5];
 
    // Initialize the array p[] as
    // {10, 20, 30, 40, 50}
    for (int i = 0; i < 5; i++) {
        p[i] = 10 * (i + 1);
    }
 
    // Print the values using pointers
    cout << *p << endl;
    cout << *p + 1 << endl;
    cout << *(p + 1) << endl;
    cout << 2 [p] << endl;
    cout << p[2] << endl;
    *p++;
 
    // Pointing to next location
    cout << *p;
 
    return 0;
}