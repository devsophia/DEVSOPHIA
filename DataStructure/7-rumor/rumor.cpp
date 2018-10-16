#include <bits/stdc++.h>
using namespace std;
#define LINK_SIZE 50

class Person {
private:
	int id;
	int link[LINK_SIZE];
	int linkNum;
public:
	Person(ifstream &inp);
	int getId(void) const {
		return this->id;
	}
	int* getLink(void) const {
		return this->link;
	}
	int getLinkNum(void) const {
		return this->linkNum;
	}
};

Person::Person(ifstream &inp) {
	int id, link, i;
	memset(this->link, 0, sizeof(int)*LINK_SIZE);
	inp >> id;
	this->id = id;
	for(i=0; inp>>link && !(link==0); ++i) {
		this->link[i] = link;
	}
	this->linkNum = --i;
}

auto getPerson(vector< Person > &people, int id) {
	vector< Person >::iterator i;
	for(i=people.begin(); i<people.end() &&
		!(id==i->getId()); ++i)
		;
	if(i<people.end())
		return i;
	else
		cout << "error : index over" << endl;
		return;
}

bool isRecord(vector< int > &record, int id)

void push(queue< int > &q, vector< int > &record, auto p) {
	int i;
	for(i=0; i<p->getLinkNum(); ++i) {
		int id = p->getLink()[i];
		if(!isRecord(record, id))
			q.push(id);
	}
}

int main()
{
	int N, x, d, i;
	vector< Person > people;
	queue< int > q;
	vector< int > record;
	ifstream inp("rumor.inp");
	ofstream out("rumor.out");
	inp >> N >> x >> d;

	for(i=0; i<N; ++i) {
		Person p(inp);
		people.push_back(p);
	}

	auto p = getPerson(people, id);
	do {
		q.push(q, record, p);
	} while(q.size() == 0)

	inp.close();
	out.close();
	return 0;
}
