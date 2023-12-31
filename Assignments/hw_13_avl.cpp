//
// ========================================
// HW13: Implement a Binary Search Tree 
//       which can be converted to AVL Tree 
// ========================================
// 
// In this assignment, we will implement 
// an AVL tree which can also do standard 
// Binary Search Tree adding and removal.  
// 
// The Node class and AVL class are both 
// partly defined for you. 
// 
// ***************************************
// You can add new variables and functions 
// in both classes. However, you should 
// implement the following given functions 
// because they will be called in the main 
// function to test part of your implementation. 
// (Check "main" function for more details.)
// 1. PreTraverse()
// 2. GetRoot()
// 3. Add()
// 4. Remove()
// 5. Add_AVL()
// 6. Remove_AVL()
// 7. Height()
// Other given functions are only recommended. 
// ***************************************
// 

#include <iostream>
#include <queue>
using namespace std;

class Node {
private:
	int key;
	Node* p_left; 
	Node* p_right;
	Node* p_parent;
public:
	void Set_key(int x);
	int Get_key();
	void Set_left(Node *p);
	void Set_right(Node* p);
	void Set_parent(Node* p);
	Node* Get_left();
	Node* Get_right();
	Node* Get_parent();
	void copy(Node* p);
	Node();
};
Node::Node() {
	key = 0;
	p_left = NULL;
	p_right = NULL;
	p_parent = NULL;
}
void Node::Set_key(int x) {
	key = x;
}
int Node::Get_key() {
	return key;
}
void Node::Set_left(Node* p) {
	p_left = p;
}
void Node::Set_right(Node* p) {
	p_right = p;
}
void Node::Set_parent(Node* p) {
	p_parent = p;
}
Node* Node::Get_left() {
	return p_left; 
}
Node* Node::Get_right() {
	return p_right;
}
Node* Node::Get_parent() {
	return p_parent; 
}
void Node::copy(Node* p){
	p_left = p->Get_left();
	p_right = p->Get_right();
	p_parent = p->Get_parent();
	key = p->Get_key();
}

class AVL {
private:
	
	// This is root of the AVL
	Node* root;

public:

	// This function implements pre-order 
	// traverse, starting from the root, 
	// and prints the traveres sequence 
	// (with no space between nodes). 
	// You can use the function you implemented 
	// in HW10 (by slightly modifying it). 
	// This function is only used to test 
	// if your updated AVL/BST is correct. 
	void PreTraverse();
	void PreTraverse(Node* root);

	// This function returns the root node. 
	// Normally we don't need it. Here we 
	// just it to evaluate your Height function.
	// See main function test case 5 for details.
	Node* GetRoot();

	// This function performs search 
	// on the current AVL with "key".
	// It returns address of a matching 
	// node, or returns NULL if no 
	// matching node is found. 
	Node* Search(int key);

	// This function adds a new node at 
	// "p" to AVL without considering 
	// any violation of AVL property. 
	// (So just standard BST adding.)
	// It can return a proper address.
	Node* Add(Node* p);

	// This function removes a node with 
	// "key" from AVL without considering 
	// any violation of AVL property. 
	// (So just standard BST removal.) 
	// For simplicty, to fill holes, let 
	// us only use the recursive algorithm 
	// that looks for the max/min node in 
	// the left/right subtress of the hole. 
	// It can return a proper address.
	Node* Remove(int key);

	// This function adds a new node 
	// stored at "p" to AVL and performs 
	// necessary rotations to restore 
	// the AVL property.
	void Add_AVL(Node* p);

	// This function removes a node 
	// with "key" from AVL and performs 
	// necessary rotations to restore 
	// the AVL property.
	void Remove_AVL(int key);

	// This function returns height 
	// of a subtree rooted at "p". 
	int Height(Node* p);

	// This function performs clock-wise
	// rotation at node "p". It only does
	// rotation and does not consider 
	// the type of violation scenario.
	// It can return a proper address.
	Node* Rotate_cw(Node* p);

	// This function performs counter 
	// clock-wise rotation at node "p". 
	// It only does rotation and does 
	// not consider the type of violation 
	// scenario. It can return a proper address.
	Node* Rotate_cc(Node* p);

	// This function checks if there 
	// is a violation at a node p, and 
	// return the violation scenario. 
	// It returns a string of 
	// - "NO" if no violation 
	// - "LL" if it is left-left violation 
	// - "RR" if it is right-right violation
	// - "LR" if it is left-right violation
	// - "RL" if it is right-left violation
	string CheckViolation(Node* p);

	// This function intiailizes root = NULL.
	AVL();
};
void AVL::PreTraverse(){
	PreTraverse(root);
}
void AVL::PreTraverse(Node* root){
	if(root == NULL){
		return;
	}
	cout << root->Get_key();
	PreTraverse(root->Get_left());
	PreTraverse(root->Get_right());
}
Node* AVL::GetRoot(){
	return root;
}
Node* AVL::Add(Node* p){
	if(root == NULL){
		root = p;
		return root;
	}
	Node* temp = root;
	while(temp != NULL){
		if(p->Get_key() > temp->Get_key()){
			if(temp->Get_right()){
				temp = temp->Get_right();
			}
			else{//if the right child of the parent node is NULL, replace it with p.
				p->Set_parent(temp);
				temp->Set_right(p);
				break;
			}
		}
		if(p->Get_key() < temp->Get_key()){
			if(temp->Get_left()){
				temp = temp->Get_left();
			}
			else{//if the left child of the parent node is NULL, replace it with p.
				p->Set_parent(temp);
				temp->Set_left(p);
				break;
			}
		}
	}
	return p;//IDK what to return here. what's a "proper address"?
}
Node* AVL::Remove(int key){
	Node* remove = Search(key);

	if(!remove){
		return NULL;
	}

	if(remove->Get_left() == NULL || remove->Get_right()){
		Node* replacement;
		if(remove->Get_left() == NULL){
			replacement = remove->Get_right();
		}
		else{
			replacement = remove->Get_left();
		}

		if(!remove->Get_parent()){
			free(remove);
			return replacement;
		}

		if(remove == remove->Get_parent()->Get_left()){
			remove->Get_parent()->Set_left(replacement);
		}
		else{
			remove->Get_parent()->Set_right(replacement);
		}
		free(remove);
	}

	else {
		Node* parent = NULL;
		Node* temp;
		temp = remove->Get_right();
		while(temp->Get_left()){
			parent = temp;
			temp = temp->Get_left();
		}
		if(parent){
			parent->Set_left(temp->Get_right());
		}
		else{
			remove->Set_right(temp->Get_right());
		}
	}
	return remove;
}
void AVL::Add_AVL(Node* p){
	Add(p);
	string violationCode = CheckViolation(root);
	while(violationCode != "NO"){
		violationCode = CheckViolation(root);	
	}
}
void AVL::Remove_AVL(int key){
	Remove(key);
	string violationCode = CheckViolation(root);
	while(violationCode != "NO"){
		violationCode = CheckViolation(root);
	}
}
int AVL::Height(Node* p){
	//code from hw10 :P
	int height = 0;

	queue<Node*> q;
	q.push(p);
	q.push(NULL);//NULL marks the end of a layer of the tree, so everytime we encounter NULL, we increment height by 1

	while(!q.empty()){
		Node *temp = q.front();
		q.pop();
		if(temp == NULL){//reached the end of a tier
			height++;
		}

		if(temp != NULL){
			if(temp->Get_left()){
				q.push(temp->Get_left());
			}
			if(temp->Get_right()){
				q.push(temp->Get_right());
			}
		}
		else if(!q.empty()){
			q.push(NULL);
		}
	}
	return height - 1;
}
Node* AVL::Rotate_cw(Node* p){
	Node* temp = p->Get_left();
	temp->Set_parent(p->Get_parent());
	p->Set_parent(temp);
	p->Set_left(temp->Get_right());
	temp->Set_right(p);
	return temp;
}
Node* AVL::Rotate_cc(Node* p){
	Node* temp = p->Get_right();
	temp->Set_parent(p->Get_parent());
	p->Set_parent(temp);
	p->Set_right(temp->Get_left());
	temp->Set_left(p);
	return temp;
}
Node* AVL::Search(int key){
	Node* temp = root;
	while(temp && key != temp->Get_key()){//I don't think this will throw an error
		if(key > temp->Get_key()){
			temp = temp->Get_right();
		}
		else{
			temp = temp->Get_left();
		}
	}
	return temp;
}
string AVL::CheckViolation(Node* p){
	queue<Node*> q;
	q.push(p);
	int leftHeight;
	int rightHeight;
	Node* violatingNode = NULL;
	while(!q.empty()){//using breadth first search to check each node
		if(q.front()->Get_left()){
			q.push(q.front()->Get_left());
			leftHeight = Height(q.front()->Get_left());
		}
		else{leftHeight = -1;}
		if(q.front()->Get_right()){
			q.push(q.front()->Get_right());
			rightHeight = Height(q.front()->Get_right());
		}
		else{rightHeight = -1;}
		if(abs(leftHeight - rightHeight) > 1){
			violatingNode = q.front();
		}
		q.pop();
	}

	string result;
	if(violatingNode && Height(violatingNode->Get_left()) > Height(violatingNode->Get_right())){
		result = "L";
		if(Height(violatingNode->Get_left()->Get_left()) > Height(violatingNode->Get_left()->Get_right())){
			result += "L";
			Rotate_cw(violatingNode);//im correcting the violations here, it still outputs a violating code after fixing the violation
		}
		else{
			result += "R";
			violatingNode->Set_left(Rotate_cc(violatingNode->Get_left()));
			Rotate_cw(root);
		}
		return result;
	}
	else if(violatingNode && Height(violatingNode->Get_left()) < Height(violatingNode->Get_right())){
		result = "R";
		if(Height(violatingNode->Get_left()->Get_left()) > Height(violatingNode->Get_left()->Get_right())){
			result += "L";
			violatingNode->Set_right(Rotate_cw(violatingNode->Get_right()));
			Rotate_cc(violatingNode);
		}
		else{
			result += "R";
			Rotate_cc(violatingNode);
		}
		return result;
	}
	return "NO";
}
AVL::AVL(){
	root = NULL;
}

// --------------
// Main Function 
// --------------
int main()
{
	// mode_test: indicate which function to test 
	// model_avl: if 1, we do adding with AVL property
	//            if 0, we do adding without AVL property 
	//            (so just standard bst adding)
	// key_temp:  keys of nodes to add to AVL initially
	// key_search:key of node for search/remove
	int mode_test, mode_avl, key_temp, key_search;
	
	Node* temp;

	// This is our AVL tree object.
	AVL tree;

	cin >> mode_test >> mode_avl >> key_search;

	while (cin >> key_temp) {

		temp = new Node;
		temp->Set_key(key_temp);

		if (mode_avl == 0)
		{
			tree.Add(temp);
		}
		else if (mode_avl == 1) {
			tree.Add_AVL(temp);
		}
	}

	// Mode 0: test "Add" function.
	if (mode_test == 0) {
		tree.PreTraverse();
	}
	// Mode 1: test "Add_AVL" function
	else if (mode_test == 1) {
		tree.PreTraverse();
	}
	// Mode 2: test "Search" function 
	else if (mode_test == 2) {
		temp = tree.Search(key_search);
		if (temp == NULL) {
			cout << -1;
		}
		else {
			cout << temp->Get_key();
		}		
	}
	// Mode 3: test "Remove" function 
	else if (mode_test == 3) {
		tree.Remove(key_search);
		tree.PreTraverse();
	}
	// Mode 4: test "Remove_AVL" function 
	else if (mode_test == 4) {
		tree.Remove_AVL(key_search);
		tree.PreTraverse();
	}
	// Mode 5: test "Height" function 
	else if (mode_test == 5) {
		cout << tree.Height(tree.GetRoot());
	}


	return 0;
};
