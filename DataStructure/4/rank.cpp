#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Student { // 학생 개인 class
private:
	int StuNum; // 학생 번호
	int AssNum; // 과제물 제출 횟수
	vector<int> Scores; // 과제물 점수저장 벡터
public:
	Student(ifstream &inp, int StuNum); // 생성자(정렬 포함)
	int getStuNum() const { // 학생번호를 얻음
		return this->StuNum;
	}
	int getAssNum() const { // 과제물 제출 횟수를 얻음
		return this->AssNum;
	}
	int getIthScore(int i) const { // i번째 과제물 점수를 얻음
		return this->Scores.at(i);
	}
};

Student::Student(ifstream &inp, int StuNum)
	: StuNum(StuNum) {
	int score;
	do {
		inp >> score;
		if(score == -1) break;
		this->Scores.push_back(score);
	} while(true);
	this->AssNum = this->Scores.size();
	sort(this->Scores.begin(), this->Scores.end()); // 학생 개개인의 점수를 오름차순으로 미리 정렬
}

class Class { // 학생들이 모인 학급 class
private:
	vector<Student> Students; // Student 저장 벡터
public:
	Class(ifstream &inp, int num); // 생성자(정렬 포함)
	void print(ofstream &out); // 정렬된 학생들의 번호를 순서대로 출력
};

bool myfunction(Student a, Student b); // 학생들을 문제에 제시된 기준에 따라 정렬하기 위한 generic sort 함수

Class::Class(ifstream &inp, int num) {
	for(int i=1; i<=num; ++i)
		this->Students.push_back(Student(inp, i));
	sort(this->Students.begin(), this->Students.end(), myfunction); // 위의 함수에 따라 정렬
}
void Class::print(ofstream &out) {
	vector<Student>::iterator i;
	for(i=Students.begin(); i!=Students.end(); ++i) {
		out << i->getStuNum() << endl;
	}
};

bool myfunction(Student a, Student b) {
	if(a.getAssNum() != b.getAssNum())
		return (a.getAssNum() > b.getAssNum());
	else {
		int i=0;
		while(a.getIthScore(i)==b.getIthScore(i) && i<a.getAssNum())
			++i;
		if(a.getIthScore(i) != b.getIthScore(i))
			return (a.getIthScore(i) > b.getIthScore(i));
		else
			return (a.getStuNum() > b.getStuNum());
	}
}

int main(void)
{
	ifstream inp;
	inp.open("rank.inp");
	ofstream out;
	out.open("rank.out");

	int num;
	inp >> num;
	Class myClass(inp, num);
	myClass.print(out);

	inp.close();
	out.close();
	return 0;
}
