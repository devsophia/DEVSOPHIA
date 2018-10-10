#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Line { // 함수 한 줄을 나타내는 클래스
private:
	vector< string > line;
	string name;
public:
	Line(ifstream &in) {
		string s;
		int i;
		this->line.resize(31, "$");
		for(i=0; in>>s && s!="$"; ++i)
			this->line[i] = s;
		this->name = this->line[0];
	}
	string getName() const { // 함수의 이름을 얻음
		return this->name;
	}
	string getJthName(const int &j) const { // j번째 연산이름을 얻음
		return this->line[j];
	}
};

bool isFunc(string s) { // jump인지 연산인지 구분
	int ASCII = (int)s[0];
	if(65 <= ASCII && ASCII <= 90)
		return true;
	return false;
}

bool isEnd(string s) { // 끝인지 구분
	if(s == "$")
		return true;
	return false;
}

void jump(vector<Line> &prog, int &i, int &j) { // 찾은 함수의 첫번째 명령어로 인덱스 이동
	int k;
	string name = prog[i].getJthName(j);
	for(k=0; !(name==prog[k].getName()); ++k)
		;
	i = k; j = 1;
}

bool isDeadLock(vector< vector<int> > &stack) { // DEADLOCK 검사 함수
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
	vector< Line > prog; // 프로그램 전체
	vector< vector<int> > stack; // 함수 스택
	vector< vector<string> > record; // 실행 레코드
	ifstream in("function.inp");
	ofstream out("function.out");
	
	in >> N >> k1 >> k2;
	for(i=0; i<N; ++i) {
		Line line(in);
		prog.push_back(line);
	}

	i=0; j=1;
	while(!(i==0 && isEnd(prog[0].getJthName(j)))) {
		string s = prog[i].getJthName(j); // i번째 함수에서 j번째 문자를 얻음
		if(isFunc(s)) { // 문자가 함수로 점프하는 연산인가 ?
			vector<int> stk(2);
			stk[0] = i; stk[1] = j;
			stack.push_back(stk);
			if(isDeadLock(stack)) break; // DEADLOCK 검사
			jump(prog, i, j);
		}
		else if(isEnd(s)) { // 함수의 끝을 만났나 ?
			i = stack.back()[0];
			j = stack.back()[1]+1;
			stack.pop_back();
		}
		else { // 일반연산인가 ?
			vector<string> rc(2);
			rc[0] = prog[i].getName();
			rc[1] = s;
			record.push_back(rc);
			++j;
		}
	}

	if(i==0 && isEnd(prog[0].getJthName(j))) { // 함수가 정상적으로 종료되었으면
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
	else // DEADLOCK 조건에 의해 탈출했으면
		out << "DEADLOCK";

	in.close();
	out.close();
	return 0;
}
