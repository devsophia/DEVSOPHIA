#include <bits/stdc++.h>
using namespace std;
#define LINK_SIZE 50

class Person {
private:
	int id;
	int link[LINK_SIZE];
public:
	Person(ifstream &inp);
};

Person::Person(ifstream &inp) {
	int id, link, i;
	memset(this->link, 0, sizeof(int)*LINK_SIZE);
	inp >> id;
	this->id = id;
	for(i=0; inp>>link && link!=0; ++i) {
		
	}
}

int main()
{
	int N, x, d;
	ifstream inp("rumor.inp");
	ofstream out("rumor.out");
	inp >> N >> x >> d;

	inp.close();
	out.close();
	return 0;
}
