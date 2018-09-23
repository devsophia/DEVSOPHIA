#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
- 입력 : K(초기 slot 수, 2<=K<=20), N(오간차의 수, 10<=N<=2^16), N개의 W(출차시 -, 1<=W<=2^16)
- 출력 : 입차된 slot번호 차량번호
- 입차시 가장 앞의 빈칸에 주차
- 주차된 차가 현재 주차공간의 1/3이하가 되면 현재 주차공간 반으로 줄이고 모두 왼쪽으로 정렬
- 현재 주차공간이 만차이고 새로운 차가 들어오려고 하면 현재주차공간*2
- 주차공간의 크기는 항상 >= K
*/
vector<int>::iterator getFirstEmpty(vector<int> &P) {
	for(vector<int>::iterator i=P.begin(); i<P.end(); i++) {
		if(*i == -1)
			return i;
	}
	cout << "No Empty Space." << endl;
}

bool isFull(vector<int> &P) {
	for(vector<int>::iterator i=P.begin(); i<P.end(); i++) {
		if(*i == -1)
			return false;
	}
	return true;
}

bool shouldCompac(vector<int> &P) {
	int empty = 0;
	for(vector<int>::iterator i=P.begin(); i<P.end(); i++) {
		if(*i == -1)
			empty++;
	}
	if(empty >= 2.0 * (float)P.size() / 3.0)
		return true;
	else
		return false;
}

vector<int>::iterator getWIter(vector<int> &P, int W) {
	for(vector<int>::iterator i=P.begin(); i<P.end(); i++) {
		if(*i == W)
			return i;
	}
	cout << "No Car Whose Number Is : " << W << endl;
}

void moveLeft(vector<int> &P) {
	vector<int>::iterator i = P.begin();
	for(vector<int>::iterator j=P.begin(); j<P.end(); j++) {
		if(*j != -1) {
			int W;
			W = *j;
			*j = -1;
			*i = W;
			i++;
		}
	}
}

void makeHalf(vector<int> &P, int &size) {
	size /= 2;
	P.resize(size, -1);
}

int main(void) {
	ifstream inp;
	inp.open("parking.inp");
	ofstream out;
	out.open("parking.out");
	int K, N, W, size;
	inp >> K >> N;
	size = K;
	vector<int> P(K, -1);

	for(int a=0; a<N; a++) {
		inp >> W;
		if(W>=0) {
			*getFirstEmpty(P) = W;
			if(isFull(P) == true) {
				size *= 2;
				P.resize(size, -1);
			}
			/*
			if(isFull(P) == true) {
				size *= 2;
				P.resize(size, -1);
				*getFirstEmpty(P) = W;
			}
			else {
				vector<int>::iterator i = getFirstEmpty(P);
				*i = W;
			}
			*/
		}
		else {
			W = -W;
			vector<int>::iterator i = getWIter(P, W);
			*i = -1;
			if(shouldCompac(P) == true) {
				moveLeft(P);
				if(size/2 >= K)
					makeHalf(P, size);
			}
		}
	}

	int k = 0;
	for(vector<int>::iterator i=P.begin(); i<P.end(); i++) {
		k++;
		if(*i != -1) {
			out << k << ' ' << *i << endl;
		}
	}
	inp.close();
	out.close();
	return 0;
}
