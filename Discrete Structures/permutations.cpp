#include <iostream>
#include <vector>
using namespace std;

vector<int> readFile(){
    return vector<int>();
}
vector<vector<int> > findPermutations(vector<int> input){
    if(input.size() == 1){
        vector<vector<int> > one;
        one.push_back(input);
        return one;
    }
    vector<vector<int> > allPerms;
    vector<int> Sx = input;
    for(int x : Sx){
        vector<int>::iterator index = find(Sx.begin(), Sx.end(), x);
        Sx.erase(index);
        for(vector<int> P : findPermutations(Sx)){
            P.push_back(x);
            allPerms.push_back(P);
        }
    }
    return allPerms;
}
int main(){
    /*
    vector<int> input = readFile();
    vector<vector<int>> permutations = findPermutations(input);
    */
    vector<vector<int> > permutations = findPermutations({1, 2, 3});
    cout << "(";
    for(vector<int> set : permutations){
        cout << "(";
        for(int element : set){
            cout << element << ", ";
        }
        cout <<")";
    }
    cout << ")";
    return 0;
}