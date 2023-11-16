#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<vector<int> > permutations;

vector<int> readFile(){
    vector<int> result(0);
    ifstream file;
    file.open("input-1.csv");
    string line;
    getline(file, line);
    int x;
    for(int i = 0; i < line.size(); i++){
        if(line[i] != ','){
            result.push_back(line[i]);
        }   
    }
    return result;
}
//returns 0 if v1 and v2 are different, 1 if they are the same
int compareArrays(vector<int> v1, vector<int> v2){
    if(v1.size() != v2.size()){
        return 0;
    }
    for(int i = 0; i < v1.size(); i++){
        if(v1[i] != v2[i]){
            return 0;
        }
    }
    return 1;
}
//returns 1 if input is in the permutations vector, 0 if not
int inArray(vector<int> input){
    for(int permutationIndex = 0; permutationIndex < permutations.size(); permutationIndex++){
        if(compareArrays(permutations[permutationIndex],input)){
            return 1;
        }
    }
    return 0;
}
//returns a 1 if v1 is comparatively larger than v2, 0 otherwise
int v1GreaterThanv2(vector<int> v1, vector<int> v2){
    if(v1.size() > v2.size()){
        return 1;
    }
    if(v1.size() < v2.size()){
        return 0;
    }
    for(int i = 0; i < v1.size(); i++){
        if(v1[i] > v2[i]){
            return 1;
        }
        else if(v1[i] < v2[i]){
            return 0;
        }
    }
    return 0;
}
void sort(){
    int i, j;
    int swapped;
    for(i = 0; i < permutations.size() - 1; i++){
        swapped = 0;
        for(j = 0; j < permutations.size() - i - 1; j++){
            if(v1GreaterThanv2(permutations[j], permutations[j + 1])){
                swap(permutations[j], permutations[j + 1]);
                swapped = 1;
            }
        }
        if(!swapped){
            return;
        }
    }
}
//places all the permutations vector, returns something for the sake of the recursion
vector<vector<int> > findPermutations(vector<int> input){
    if(input.size() == 0){
        vector<vector<int> > nothing;
        return nothing;
    }
    if(input.size() == 1){
        vector<vector<int> > one;
        one.push_back(input);
        if(!inArray(input)){
            permutations.push_back(input);
        }
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
            if(!inArray(P)){
                permutations.push_back(P);
            }
        }
        Sx = input;
    }
    sort();
    return allPerms;
}
void writeFile(){

}
int main(){
    vector<int> input = readFile();
    findPermutations(input);
    writeFile();
    cout << "(";
    for(vector<int> set : permutations){
        cout << "(";
        for(int element : set){
            if(element == set[set.size() - 1]){
                cout << element;
            }
            else{
                cout << element << ", ";
            }
        }
        if(set == permutations[permutations.size() - 1]){
            cout << ")";
        }
        else{
            cout <<"),";
        }
    }
    cout << ")";
    return 0;
}