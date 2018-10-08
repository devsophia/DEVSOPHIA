#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Line {
private:
	vector< string > line;
	int len;
	string name;
	int deadNum;
public:
	Line(ifstream &in) : deadNum(0) {
		string s;
		int i;
		this->line.resize(31, "$");
		for(i=0; in>>s && s!="$"; ++i)
			this->line[i] = s;
		this->len = i;
		this->name = this->line[0];
	}
	int getLen() const {
		return this->len;
	}
	string getName() const {
		return this->name;
	}
	string getJumpName(const int &j) const {
		return this->line[j];
	}
};

bool isFunc(string s) { // jump인지 명령어인지 구분
	int ASCII = (int)s[0];
	if(65 <= ASCII && ASCII <= 90)
		return true;
	return false;
}

bool isEnd(string s) {
	if(s == "$")
		return true;
	return false;
}

void jump(vector<Line> &prog, int &i, int &j) { // 찾은 함수의 첫번째 명령어로 인덱스 이동
	int k;
	string name = prog[i].getJumpName(j); // 점프할 함수의 이름
	for(k=0; !(name==prog[k].getName()); ++k) // 같아질 때까지
		;
	i = k; j = 1; // 인덱스 set
}

bool isDeadLock(vector< vector<int> > &stack) {
	int i, size;
	size = stack.size();
	for(i=0; i<size-1 && 
		!(stack.back()[0] == stack[i][0] && stack.back()[1] == stack[i][1]); ++i)
		;
	if(i<size-1)
		return true;
	return false;
}

int main()
{
	int N, k1, k2, i, j;
	vector< Line > prog;
	vector< vector<int> > stack;
	vector< vector<string> > record;
	ifstream in("function.inp");
	ofstream out("function.out");
	
	in >> N >> k1 >> k2;
	for(i=0; i<N; ++i) {
		Line line(in);
		prog.push_back(line);
	}

	i=0; j=1;
	while(!(i==0 && isEnd(prog[0].getJumpName(j)))) {
		string s = prog[i].getJumpName(j);
		if(isFunc(s)) {
			vector<int> stk(2);
			stk[0] = i; stk[1] = j;
			stack.push_back(stk);
			if(isDeadLock(stack)) break;
			jump(prog, i, j);
		}
		else if(isEnd(s)) {
			i = stack.back()[0];
			j = stack.back()[1]+1;
			stack.pop_back();
		}
		else {
			vector<string> rc(2);
			rc[0] = prog[i].getName();
			rc[1] = s;
			record.push_back(rc);
			++j;
		}
	}

	if(i==0 && isEnd(prog[0].getJumpName(j))) {
		int sz = record.size();
		if(k1 > sz)
			out << "NONE" << endl;
		else
			out << record[k1-1][0] << "-"
				<< record[k1-1][1] << endl;
		if(k2 > sz)
			out << "NONE" << endl;
		else
			out << record[k2-1][0] << "-"
				<< record[k2-1][1] << endl;
	}
	else
		out << "DEADLOCK";

	in.close();
	out.close();
	return 0;
}
