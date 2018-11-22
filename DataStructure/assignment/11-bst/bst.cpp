#include <bits/stdc++.h>
using namespace std;

/*  조교님께
	템플릿에 대한 개념이 부족하여
	연습할 겸 직접 구현해 보았습니다.
*/

class TreeNode {
private:
	int data;
	TreeNode* pRight;
	TreeNode* pLeft;
public:
	TreeNode(int data) : data(data),
		pLeft(NULL), pRight(NULL) {}
	const int getData() const {
		return this->data;
	}
	TreeNode* getLeft() const {
		return this->pLeft;
	}
	TreeNode* getRight() const {
		return this->pRight;
	}
	void setLeft(TreeNode* pLeft) {
		this->pLeft = pLeft;
	}
	void setRight(TreeNode* pRight) {
		this->pRight = pRight;
	}
	void print(int l) {
		if(this) {
			this->pRight->print(l+1);
			for(int i=0; i<l; ++i)
				cout << "   ";
			cout << this->data << endl;
			this->pLeft->print(l+1);
		}
	}
	void deAlloc() {
		if(this) {
			this->pLeft->deAlloc();
			this->pRight->deAlloc();
			delete(this);
		}
	}
};

class BST {
private:
	TreeNode* root;
public:
	BST() : root(NULL) {}
	void insert(int n);
	void find(int n) const;
	void print() const;
	~BST();
};

void BST::insert(int n) {
	TreeNode* pNode = new TreeNode(n);
	if(this->root == NULL)
		this->root = pNode;
	else {
		TreeNode* pCurrent = this->root;
		TreeNode* pNext = NULL;
		while((pNext=n<pCurrent->getData()?
			pCurrent->getLeft():pCurrent->getRight())
			!=NULL)
			pCurrent = pNext;
		if(n<pCurrent->getData())
			pCurrent->setLeft(pNode);
		else
			pCurrent->setRight(pNode);
	}
	
}

void BST::find(int n) const {
	int depth = 0;
	TreeNode* pCurrent = this->root;
	while(pCurrent!=NULL && pCurrent->getData()!=n) {
		pCurrent = n<pCurrent->getData()?
			pCurrent->getLeft():pCurrent->getRight();
		depth++;
	}
	if(pCurrent==NULL)
		cout << "No node exists whose data is " <<
			n << "." << endl;
	else
		cout << "Number " << n << " exists at depth " <<
			depth << "." << endl;
}

void BST::print() const {
	this->root->print(0);
}

BST::~BST() {
	this->root->deAlloc();
}

void guide() {
	cout << endl;
	cout << "Type one of instructions below." << endl;
	cout << "{exit, insert x, find x, print}" << endl;
	cout << "=>";
}

int getCase(string inst) {
	string sequence[] = {"exit", "insert", "find", "print"};
	int i, size = sizeof(sequence)/sizeof(sequence[0]);
	for(i=0; i<size; ++i)
		if(sequence[i] == inst)
			return i;
	return -1;
}

int main(void)
{
	BST bst;
	string inst;
	int num;
	bool endFlag = false;
	while(!endFlag) {
		guide();
		cin >> inst;
		switch(getCase(inst)) {
		case 0:
			cout << "Turning off machine.." << endl;
			endFlag = true;
			break;
		case 1:
			cin >> num;
			bst.insert(num);
			break;
		case 2:
			cin >> num;
			bst.find(num);
			break;
		case 3:
			bst.print();
			break;
		default:
			cout << "No such instruction." << endl;
			cout << "Please try again." << endl;
		}
	}
	return 0;
}
