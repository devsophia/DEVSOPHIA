#include <bits/stdc++.h>
using namespace std;

class BST;

class Node {
private:
	friend class BST;
	string data;
	Node *Left, *Right;
public:
	Node(string data)
		: data(data), Left(NULL), Right(NULL) {}
	bool isLeaf() { return Left==NULL && Right==NULL; }
	void depth(vector<string> &v, int depth, int k);
	void leaf(vector<string> &v);
};
void Node::depth(vector<string> &v, int depth, int k) {
	if(this->Left)
		this->Left->depth(v, depth+1, k);
	if(this->Right)
		this->Right->depth(v, depth+1, k);
	if(depth == k)
		v.push_back(this->data);
}
void Node::leaf(vector<string> &v) {
	if(this->isLeaf()) {
		v.push_back(this->data);
		return;
	}
	if(this->Left)
		this->Left->leaf(v);
	if(this->Right)
		this->Right->leaf(v);
}

class BST {
private:
	Node *root;
public:
	BST() {
		this->root = new Node("a");
	}
	void insert(string data);
	void erase(string data);
	vector<string> depth(int k);
	vector<string> leaf();
};
void BST::insert(string data) {
	Node *pNew = new Node(data);
	Node *pParent, *pChild;
	bool left;
	pChild = this->root;
	do {
		pParent = pChild;
		left = data.compare(pParent->data) < 0;
		pChild = left ? pParent->Left : pParent->Right;
	} while(pChild != NULL);
	if(left)
		pParent->Left = pNew;
	else
		pParent->Right = pNew;
}
void BST::erase(string data) {
}
vector<string> BST::depth(int k) {
	vector<string> v;
	this->root->depth(v, 0, k);
	return v;
}
vector<string> BST::leaf() {
	vector<string> v;
	this->root->leaf(v);
	return v;
}

int getCase(string inst);
void print_depth(vector<string> &v, ofstream &out);
void print_leaf(vector<string> &v, ofstream &out);

int main(void)
{
	int N, k;
	string inst, data;
	BST bst;
	vector<string> d, l;
	ifstream inp("1.inp");
	ofstream out("bst.out");
	inp >> N;
	while(N--) {
		inp >> inst;
		switch(getCase(inst)) {
		case 0:
			inp >> data;
			bst.insert(data);
			break;
		case 1:
			inp >> data;
			bst.erase(data);
			break;
		case 2:
			inp >> k;
			d = bst.depth(k);
			print_depth(d, out);
			break;
		case 3:
			l = bst.leaf();
			print_leaf(l, out);
			break;
		default:
			out << "Wrong Instruction : " <<
			inst << endl;
		}
	}
	inp.close();
	out.close();
	return 0;
}

int getCase(string inst) {
	string list[] = {"+", "-", "depth", "leaf"};
	for(int i=0; i<sizeof(list)/sizeof(list[0]); ++i)
		if(list[i] == inst)
			return i;
	return -1;
}
void print_depth(vector<string> &v, ofstream &out) {
	if(v.size()==0) {
		out << "NO" << endl;
		return;
	}
	for(auto it=v.begin(); it!=v.end(); ++it)
		out << *it << " ";
	out << endl;
}
void print_leaf(vector<string> &v, ofstream &out) {
	for(auto it=v.begin(); it!=v.end(); ++it)
		out << *it << " ";
	out << endl;
}
