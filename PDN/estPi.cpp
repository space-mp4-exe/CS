#include <iostream>

using namespace std;

//estimates pi
int main(){
    double factor = 1.0;
    double sum = 0.0;
    int k = 0; 
    int n = 100000000;
    for(k = 0; k < n; k++){
        sum += factor/(2*k+1);
        factor = -factor;
    }
    cout << 4 * sum << endl;
    return 0;
}
