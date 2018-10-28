#include <bits/stdc++.h>
using namespace std;

/*
	첫 줄에는 벡터의 크기 N과 swap 작업의 수 k가 주어진다.
	swap시 순서가 뒤바뀌고 부호가 바뀐다.
	그 다음 줄에는 beg, end가 k만큼 주어진다.
*/

void swap(vector<int> &v, int b, int e)
{
	int i, j, temp;
	for(i=b, j=e; i<j; ++i, --j) {
		temp = -v[i];
		v[i] = -v[j];
		v[j] = temp;
	}

	if((e-b)%2 == 0)
		v[i] = -v[i];
}

int main(void)
{
	int N, k, i=0;
	int b, e;
	vector< int > v;

	cin >> N >> k;
	while(N--)
		v.push_back(i++);
	v.push_back(i);

	while(k--) {
		cin >> b >> e;
		swap(v, b, e);
	}

	for(i=0; i<v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;

	return 0;
}
