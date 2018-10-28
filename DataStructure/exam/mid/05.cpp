#include <bits/stdc++.h>
using namespace std;

/*
	seta-setb 구현
*/

void move_forward(vector< int > &v,
	vector< int >::iterator it)
{
	for(; it!=v.end()-1; ++it) {
		*it = *(it+1);
	}
}

int main()
{
	vector< int > seta = {4, 11, 2, 5, 5, 6, 30, 7, 50};
	vector< int > setb = {44, 555, 600};
	auto it = seta.begin();
	auto jt = setb.begin();
	int acc=0;

	for(; jt!=setb.end(); ++jt) {
		for(it=seta.begin(); it!=seta.end(); ++it) {
			if(*jt == *it) {
				move_forward(seta, it);
				--it;
				++acc;
			}
		}
	}

	while(acc--)
		seta.pop_back();

	for(it=seta.begin(); it!=seta.end(); it++) {
		printf(" %d ", *it);
	}
	return 0;
}
