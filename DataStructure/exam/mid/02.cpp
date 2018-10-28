#include <bits/stdc++.h>
using namespace std;

/*
	제일 앞의 stack부터 선택한다.
	선택된 stack의 top원소가 x보다 작으면 그 stack에 넣고,
	크면 그 다음 stack에 넣는다.
*/

int main(void)
{
	int N, num, i;
	vector< stack< int > > v;
	stack< int > s;
	v.push_back(s);
	cin >> N;

	while(N--) {
		i = 0;
		cin >> num;
		while(true) {
			if(v[i].size()>0 && v[i].top()<num) {
				if(v.size()-1 == i) {
					stack< int > ss;
					v.push_back(ss);
				}
				++i;
			}
			if(v[i].size()==0 || (v[i].size()>0 && v[i].top()>num))
				break;
		}
		v[i].push(num);
	}

	for(i=0; i<v.size(); ++i) {
		while(v[i].size() != 0) {
			cout << v[i].top() << " ";
			v[i].pop();
		}
		cout << endl;
	}

	return 0;
}
