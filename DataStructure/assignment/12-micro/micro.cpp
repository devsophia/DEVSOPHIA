#include <bits/stdc++.h>
using namespace std;

class Field;
class Lump;

// individual cells
class Cell {
friend class Field;
private:
	bool pixel; // if this pixel is virus or not
	Lump *pLump; // master lump of this cell
public:
	Cell(bool pixel) : pixel(pixel), pLump(NULL) {}
};

// set of cells
class Lump {
private:
	vector<Cell*> lump; // save cell as a pointer
public:
	Lump() {}
	void addCell(Cell *pCell);
	int getSize();
};
// add a cell as a member of this lump
void Lump::addCell(Cell *pCell) {
	this->lump.push_back(pCell);
}
int Lump::getSize() {
	return this->lump.size();
}

// all is here
class Field {
private:
	int width, height; // size of field(pixel)
	vector<vector<Cell*>> field; // 2 dimensional vector has all individual cell pointers
	vector<Lump*> lumps; // lump vector has all lump pointers
public:
	Field(int &N, int &M, ifstream &inp);
	void propagate(int i, int j, Lump *pByLump);
	void traverse();
	static bool trans(string &s);
	int getLumpNum(int k);
	int getMaxSize(int k);
};
// initialization
Field::Field(int &N, int &M, ifstream &inp)
	: width(N), height(M) {
	string s;
	bool pixel;
	for(int i=0; i<M; ++i) {
		vector<Cell*> line;
		for(int j=0; j<N; ++j) {
			inp >> s;
			pixel = Field::trans(s);
			Cell *c = new Cell(pixel);
			line.push_back(c);
		}
		this->field.push_back(line);
	}
}
// recursive function which propagate virus.
// this cell is [i, j] and provided with lump nearby him.
void Field::propagate(int i, int j, Lump *pByLump) {
	Lump *pMyLump;
	// out of range
	if(i<0 || this->height<=i ||
		j<0 || this->width<=j)
		return;
	Cell *pCell = this->field[i][j];
	// not a virus pixel
	if(!(pCell->pixel))
		return;
	// already has a master lump
	if(pMyLump = pCell->pLump)
		return;
	// propagated lump doesn't exist
	if(!pByLump) {
		pMyLump = new Lump(); // make new lump
		pMyLump->addCell(pCell); // add this cell to new lump
		pCell->pLump = pMyLump; // register new lump as this cell's master lump
		this->lumps.push_back(pMyLump); // register new lump to vector of lump
	}
	// propagated lump exist
	else {
		pCell->pLump = pByLump; // register propagated lump as this cell's master lump
		pByLump->addCell(pCell); // add this cell to propagated lump
		pMyLump = pByLump; // this is required to pass parameter at below
	}
	// pass this cell's lump to nearby cells.
	propagate(i+1, j, pMyLump);
	propagate(i-1, j, pMyLump);
	propagate(i, j+1, pMyLump);
	propagate(i, j-1, pMyLump);
}
void Field::traverse() {
	for(int i=0; i<this->height; ++i)
		for(int j=0; j<this->width; ++j)
			propagate(i, j, NULL);
}
bool Field::trans(string &s) {
	if(s == "#")
		return true;
	return false;
}
// get the number of lumps whose number of child cells is more than k.
int Field::getLumpNum(int k) {
	int cnt = 0;
	for(int i=0; i<this->lumps.size(); ++i) {
		if(this->lumps[i]->getSize()>=k)
			cnt++;
	}
	return cnt;
}
// get the size of lump which has the biggest size amongst all lumps.
// if there is no lump whose number of child cell is more than k, return 0.
int Field::getMaxSize(int k) {
	int max = k, compare, cnt = 0;
	for(int i=0; i<this->lumps.size(); ++i) {
		compare = this->lumps[i]->getSize();
		if(max <= compare) {
			max = compare;
			++cnt;
		}
	}
	if(cnt == 0)
		return 0;
	return max;
}

int main(void)
{
	int N, M, k;

	ifstream inp("micro.inp");
	ofstream out("micro.out");
	inp >> N >> M >> k;
	Field field(N, M, inp);

	field.traverse();

	out << field.getLumpNum(k) << " "
		<< field.getMaxSize(k);

	inp.close();
	out.close();
	return 0;
}
