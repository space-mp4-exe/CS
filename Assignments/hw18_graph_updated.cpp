//
// ========================================
// HW18: Implement Graph, Graph Traverse
//       and Dijkstra's algorithm. 
// ========================================
// 
// In this assignment, we will implement an 
// undirected graph, two traverse algorithms 
// and the Dijkstra's algorithm. 
//  
// This template is based on matrix-based 
// graph implementation, but you are free 
// to work on list-based graph implementation. 
// 
// For simplicity, the template assumes no 
// satellite data is used and focuses on 
// dealing with integers (node numbers) only. 
// 
// Finally, feel free to modify the given template 
// including the classes, functions, etc. Just make 
// sure the outputs of functions tested in "main" 
// stay the same (for auto-grading). 
// 

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Result {
public:
    int length; 
    int weight;
    int* path;
};

// Please complete the graph class. 
// Remember this is an undirected graph 
// of "size" nodes labeled from 0 to size-1. 
class Graph {

private:

    // this variable holds the matrix 
    int** m;

    // this variable holds the number of nodes in graph 
    int size;

    void printGraph();
    int inArray(int* arr, int i);

public:

    // this function returns the degree of node i 
    int Degree(int i);


    // this function adds an edge between node i and 
    // node j, and assigns a weight "w" to the edge 
    // 
    // recall: if we do not want a weighted graph, 
    // simply set w = 1 for all edges 
    //
    // you may also check boundary but in the testing 
    // samples we assume all inputs are within boundary 
    void Add(int i, int j, int w);


    // this function returns 1 if node i and 
    // node j are connected and returns 0 otherwise.
    // 
    // note: you can also let it return the weight;  
    //       weight is zero if no edge exists 
    int IsEdge(int i, int j);


    // this function returns 1 if there is a path 
    // from node i to node j and returns 0 otherwise.  
    int IsPath(int i, int j);


    // this function performs depth-first search 
    // starting at node i. break any tie based on 
    // node number (smaller node goes first) e.g., 
    // if you can pick node 2 or node 3, pick 2. 
    // at last, this function should return an array 
    // of size n holding the traverse sequence of nodes. 
    // (Assume input graph is always connected.)
    int* DFT(int i);


    // this function performs breadth-first search 
    // starting at node i. when exploring neighbors 
    // of a set of nodes, explore them based on the 
    // order of nodes in the queue. 
    // 
    // this means once you pop a node from the queue, 
    // add its neighbors to the queue. (here, break 
    // ties based on neighbor node numbers -- smaller 
    // node gets added to the queue first)
    // 
    // at last, this function should return an array 
    // of size n holding the traverse sequence of nodes. 
    int* BFT(int i);

    // 
    // The following performs the Dijkstra's algorithm
    // to find the shorest path from node i to node j.  
    // 
    // It returns address of an object of the 
    // Result class, which contains three 
    // public variables (see definition at top): 
    // (i) int length: length of the shorest path 
    // (ii) int weight: total weight of the shortest path
    // (iii) int *path: array of nodes on the path 
    // Example: 
    // If the shortest path is 2 -> 3 -> 0, and 
    // weight on (2,3) is 5 and weight on (3,0) is 1, 
    // then path[0] = 2, path[1] = 3, path[2] = 0
    // and length = 3 and weight = 6. 
    // 
    Result* Dijkstra(int i, int j);


    // this is the constructor with input arguments 
    // remember to allocate space for matrix "m" and 
    // initialize all entries to zero 
    // 
    // Initialization is important because in "main" 
    // we only add edges to the matrix and assume its 
    // rest entries are zeros. 
    Graph(int n);
};
void Graph::printGraph(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}
int Graph::Degree(int i){
    int degree = 0;
    for(int j = 0; j < size; j++){
        if(m[i][j]){
            degree++;
        }
    }
    return degree;
}
void Graph::Add(int i, int j, int w){
    if(i >= size || j >= size){
        return;
    }
    m[i][j] = w;
    m[j][i] = w;
}
int Graph::IsEdge(int i, int j){
    if(i >= size || j >= size){
        return 0;
    }
    return m[i][j] != 0;
}
int Graph::inArray(int* arr, int i){
    for(int index = 0; index < size; index++){
        if(i == arr[index]){
            return 1;
        }
    }
    return 0;
}
int Graph::IsPath(int i, int j){
    int* connections = DFT(i);
    return inArray(connections, j);
}
int* Graph::DFT(int i){
    stack<int> backtrack;
    backtrack.push(i);
    int* result = new int[size];
    int* visited = new int[size];
    int resultIndex = 0;

    for(int index = 0; index < size; index++){
        visited[index] = 0;
    }

    while(!backtrack.empty()){
        int current = backtrack.top();
        backtrack.pop();
        
        if(!visited[current]){
            visited[current] = 1;
            result[resultIndex] = current;
            resultIndex++;
            for(int i = size - 1; i >= 0; i--){
                if(m[current][i] && !visited[i]){
                    backtrack.push(i);
                }
            }
        }
    }
    return result;
}
int* Graph::BFT(int i){
    int* result = new int();
    int* visited = new int[size];
    for(int j = 0; j < size; j++){
        visited[j] = 0;
    }

    queue<int> toVisit;
    toVisit.push(i);
    return result;
}
Result* Graph::Dijkstra(int i, int j){
    Result* result = new Result();
    return result;
}
Graph::Graph(int n){
    size = n;
    m = new int*[n];
    for(int i = 0; i < n; i++){
        m[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = 0;
        }
    }
}


int main()
{

    int mode, size, i, j, w;

    int a, b; // node numbers used for testing 

    cin >> mode >> size >> a >> b;

    Graph x(size);

    // each time input a pair 
    // of indices and a weight 
    // remember to separate them 
    // when inputing from keyboard 
    // also, we assume inputs are 
    // within boundary 
    while (cin >> i >> j >> w) {
        x.Add(i, j, w);
    }

    // Mode 0: test IsEdge()
    if (mode == 0) {
        cout << x.IsEdge(a, b);
    }
    // Mode 1: test IsPath()
    else if (mode == 1) {
        cout << x.IsPath(a, b);
    }
    // Mode 2: test Degree()
    else if (mode == 2) {
        cout << x.Degree(a);
    }
    // Mode 3: test DFT()
    else if (mode == 3) {
        int* s = new int[size];
        s = x.DFT(a);
        for (int i = 0; i < size; i++) {
            cout << s[i];
        }
    }
    // Mode 4: test BFT()
    else if (mode == 4) {
        int* s = new int[size];
        s = x.BFT(a);
        for (int i = 0; i < size; i++) {
            cout << s[i];
        }
    }
    // Mode 5: test Dijkstra()
    else if (mode == 5) {
        Result *z = x.Dijkstra(a, b);
        cout << z->length << endl;
        cout << z->weight << endl;
        for (int i = 0; i < z->length; i++) {
            cout << z->path[i];
        }
    }

    return 0;

}
