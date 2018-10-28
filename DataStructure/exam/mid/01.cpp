#include <bits/stdc++.h>
using namespace std;

/*
	2차원 벡터의 원소가 한줄에 하나씩 주어진다. (끝은 0)
	원소들을 한칸씩 앞으로 하는 것을 구현.
	제일 첫번째 원소는 제일 마지막으로.
*/

void move_forward(vector< int > &a)
{
	int i;
	for(i=0; i<a.size()-1; ++i)
		a[i] = a[i+1];
}

void pass(vector< int > &a,
	vector< int > &b)
{
	int i = a.size()-1;
	if(b.size() > 0)
		a[i] = b[0];
}

int main(void)
{
	int num, i, t;
	vector< vector< int > > vv;
	vector< int > v;
	while(cin >> num) {
		if(num != 0)
			v.push_back(num);
		else {
			vv.push_back(v);
			v.resize(0);
		}
	}

	t = vv[0][0];
	for(i=0; i<vv.size()-1; ++i) {
		move_forward(vv[i]);
		pass(vv[i], vv[i+1]);
	}
	move_forward(vv[i]);
	vv[i].back() = t;

	for(i=0; i<vv.size(); ++i) {
		for(int j=0; j<vv[i].size(); ++j)
			cout << vv[i][j] << " ";
		cout << 0 << endl;
	}
	
	return 0;
}
