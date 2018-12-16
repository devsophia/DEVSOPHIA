#include <bits/stdc++.h>
using namespace std;

class BST;

class Node {
friend class BST;
private:
	string data;
	Node *Left, *Right;
public:
	Node(string data)
		: data(data), Left(NULL), Right(NULL) {}
	bool isLeaf() { return Left==NULL && Right==NULL; }
	void depth(vector<string> &v, int depth, int k);
	void leaf(vector<string> &v);
	void printTreeModule(int space);
};
void Node::depth(vector<string> &v, int depth, int k) {
	if(depth == k) {
		v.push_back(this->data);
		return;
	}
	if(this->Left)
		this->Left->depth(v, depth+1, k);
	if(this->Right)
		this->Right->depth(v, depth+1, k);
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
void Node::printTreeModule(int space) {
	if(this->Right)
		this->Right->printTreeModule(space+1);

	for(int i=0; i<space; ++i)
		cout << "      ";
	cout << this->data << endl << endl;

	if(this->Left)
		this->Left->printTreeModule(space+1);
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
	void printTree();
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
	Node *pParent, *pDelete, *pChild = this->root, *pReplace = NULL;
	bool left;
	do {
		pParent = pChild;
		left = data.compare(pParent->data) < 0;
		pChild = left ? pParent->Left : pParent->Right;
	} while(pChild != NULL && pChild->data != data);
	if(pChild == NULL) {
		cout << "Cannot find node whose data is " << data << endl;
		return;
	}
	else
		pDelete = pChild;
	while(true) {
		if(pDelete->isLeaf()) {
			if(left)
				pParent->Left = NULL;
			else
				pParent->Right = NULL;
			delete(pDelete);
			return;
		}
		else {
			if(pDelete->Left) {
				bool left2;
				Node *pMax=NULL, *pMaxParent=NULL;
				pMax = pDelete->Left;
				pMaxParent = pDelete;
				while(pMax->Right) {
					pMaxParent = pMax;
					pMax = pMax->Right;
				}
				pReplace = new Node("replace");
				pReplace->Left = pMax->Left;
				pReplace->Right = pMax->Right;
				if(pMaxParent == pDelete) {
					pMaxParent->Left = pReplace;
					left2 = true;
				}
				else {
					pMaxParent->Right = pReplace;
					left2 = false;
				}
				pMax->Left = pDelete->Left;
				pMax->Right = pDelete->Right;
				if(left)
					pParent->Left = pMax;
				else
					pParent->Right = pMax;
				if(pMaxParent == pDelete)
					pParent = pMax;
				else
					pParent = pMaxParent;
				delete(pDelete);
				pDelete = pReplace;
				left = left2;
			}
			else if(pDelete->Right) {
				bool left2;
				Node *pMin, *pMinParent;
				pMin = pDelete->Right;
				pMinParent = pDelete;
				pReplace = new Node("replace");
				while(pMin->Left) {
					pMinParent = pMin;
					pMin = pMin->Left;
				}
				pReplace->Left = pMin->Left;
				pReplace->Right = pMin->Right;
				if(pMinParent == pDelete) {
					pMinParent->Right = pReplace;
					left = false;
				}
				else {
					pMinParent->Left = pReplace;
					left = true;
				}
				pMin->Left = pDelete->Left;
				pMin->Right = pDelete->Right;
				if(left)
					pParent->Left = pMin;
				else
					pParent->Right = pMin;
				if(pMinParent == pDelete)
					pParent = pMin;
				else
					pParent = pMinParent;
				delete(pDelete);
				pDelete = pReplace;
				left = left2;
			}
		}
	}
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

void BST::printTree() {
	this->root->printTreeModule(0);
}

int getCase(string inst);
void print_depth(vector<string> &v, ofstream &out);
void print_leaf(vector<string> &v, ofstream &out);

BST bst;

int main(void)
{
	int N, k;
	string inst, data;
	vector<string> d, l;
	ifstream inp("bst.inp");
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
