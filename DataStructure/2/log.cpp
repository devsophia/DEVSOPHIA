#include <iostream>
#include <fstream>
using namespace std;

class LogTable {
private:
	int** table;
	int* accNum;
	int row;
public:
	LogTable();
	const int getDay(const int row) const;
	const int getTime(const int row, const int n) const;
	const int getAccNum(const int n) const;
	const int getRow(void) const;
	~LogTable();
};

LogTable::LogTable() {
	int nOfLine, temp[10000];
	ifstream logIn;
	logIn.open("syslog.txt", ios::in);
	logIn >> nOfLine;
	this->table = new int*[nOfLine];
	this->accNum = new int[nOfLine];

	for(int i=0; i<nOfLine; i++) {
		int len = 0;
		while(logIn >> temp[len]) {
			if(temp[len] == 0) break;
			len++;
		}
		this->table[i] = new int[len];
		for(int k=0; k<len; k++) {
			this->table[i][k] = temp[k];
		}
		this->accNum[i] = len;
	}

	logIn.close();

	this->row = nOfLine;
}

LogTable::~LogTable() {
	for(int i=0; i<this->row; i++) {
		delete[] table[i];
	}
	delete[] table;
	delete[] accNum;
}

const int LogTable::getDay(const int row) const {
	return this->table[row][0];
}
const int LogTable::getTime(const int row, const int n) const {
	return this->table[row][n];
}
const int LogTable::getAccNum(const int n) const {
	return this->accNum[n];
}
const int LogTable::getRow(void) const {
	return this->row;
}

int calAccNum(const LogTable &Log, const int ds, const int ts, const int de, const int te) {
	int num = 0;
	int start = 0, end = 0;
	if(ds > Log.getDay(Log.getRow()-1))
		return 0;
	for(int row = 0; row < Log.getRow(); row++) {
		if(Log.getDay(row) >= ds) {
			start = row;
			break;
		}
	}
	if(de > Log.getDay(Log.getRow()-1))
		end = Log.getRow()-1;
	else {
		for(int row=0; row < Log.getRow(); row++) {
			if(Log.getDay(row) > de) {
				end = row - 1;
				break;
			}
			else if(Log.getDay(row) == de) {
				end = row;
				break;
			}
		}
	}
	for(int i=start; i<=end; i++) {
		num = num + Log.getAccNum(i) - 1;
	}
	if(Log.getDay(start) == ds) {
		int last = Log.getAccNum(start) - 1;
		for(int i=1; i<=last; i++) {
			if(Log.getTime(start, i) < ts)
				num--;
		}
	}
	if(Log.getDay(end) == de) {
		int last = Log.getAccNum(end) - 1;
		for(int i=1; i<=last; i++) {
			if(Log.getTime(end, i) > te)
				num--;
		}
	}
	return num;
}

int main(void)
{
	LogTable Log;
	int nOfLine;

	ifstream inp;
	inp.open("log.inp");
	inp >> nOfLine;

	ofstream out;
	out.open("log.out");

	for(int i=0; i<nOfLine; i++) {
		int ds, ts, de, te, accNum;
		inp >> ds >> ts >> de >> te;
		accNum = calAccNum(Log, ds, ts, de, te);
		out << accNum;
		if(i != nOfLine-1)
			out << endl;
	}

	out.close();
	inp.close();
	return 0;
}
