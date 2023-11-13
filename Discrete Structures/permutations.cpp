#include <iostream>
#include <vector>
using namespace std;

vector<int> readFile(){
    return vector<int>();
}
vector<vector<int> > findPermutations(vector<int> input){
    if(input.size() == 0){
        vector<vector<int> > nothing;
        return nothing;
    }
    if(input.size() == 1){
        vector<vector<int> > one;
        one.push_back(input);
        return one;
    }
    vector<vector<int> > allPerms;
    vector<int> Sx = input;
    for(vector<int>::iterator it = Sx.begin(); it != Sx.end(); it++){
        int x = *it;
        Sx.erase(it);
        
        for(vector<int> P : findPermutations(Sx)){
            P.push_back(x);
            allPerms.push_back(P);
        }
        Sx = input;
    }
    return allPerms;
}
int main(){
    /*
    vector<int> input = readFile();
    vector<vector<int>> permutations = findPermutations(input);
    */
    vector<int> input;
    input.push_back(1); input.push_back(2); input.push_back(3);
    vector<vector<int> > permutations = findPermutations(input);
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