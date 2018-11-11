#include <bits/stdc++.h>
using namespace std;

int main(void) {
	int cntGood = 0, cntBad = 0;
	string A, B;
	ifstream inp1("3.out"), inp2("log.out");
	while(inp1 >> A && inp2 >> B)
		if(A != B) {
			cout << A << "!=" << B << endl;
			cntBad++;
		}
		else
			cntGood++;
			
	cout << "comparison over." << endl;
	cout << "match : " << cntGood << endl;
	cout << "unmatch : " << cntBad << endl;
	return 0;
}
