#include <iostream>
using namespace std;

class Student {
 public:
  void set_SID(int x);
  void print_SID();
  Student();

 private:
  int SID;
};

void Student::set_SID(int x) { SID = x; };
void Student::print_SID() { cout << "SID = " << SID << endl; };

Student::Student() { SID = 0; }

int main() {
  int x, y, z = 5;
  cout << x << endl;
  cout << z << endl;
  Student x;
  x.print_SID();
  x.set_SID(30);
  x.print_SID();
  // cout << x.SID;
  return 0;
}