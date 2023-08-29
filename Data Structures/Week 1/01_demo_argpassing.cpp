#include <iostream>
using namespace std;
int main() {
  int x = 5;
  void Increment_1(int a);
  void Increment_2(int &a);
  Increment_1(x);
  cout << x << endl;
  Increment_2(x);
  cout << x << endl;
  return 0;
}
void Increment_1(int a) { a++; }
void Increment_2(int &a) { a++; }