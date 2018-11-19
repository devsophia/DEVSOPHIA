#include <bits/stdc++.h>
using namespace std;

class Group;

class Person {
private:
	string name, bName;
	Person* pBoss;
	int numOfUnder;
	int distance;
public:
	Person(string &uName, string &bName, Group* pGroup);
	Person(string &uName)
		: name(uName), bName("none"), pBoss(NULL), numOfUnder(0),
		distance(0) {
	}
	string getName() const {
		return name;
	}
	bool isBoss() const {
		if(pBoss == NULL)
			return true;
		return false;
	}
	Person* getPBoss() const {
		return this->pBoss;
	}
	void setDistance(int cnt) {
		distance = cnt;
	}
	void addNum() {
		++numOfUnder;
	}
	int getNum() const {
		return numOfUnder;
	}
	int getDistance() const {
		return distance;
	}
	void setBoss(Person* p) {
		this->pBoss = p;
		this->bName = p->name;
	}
};

class Group {
private:
	vector<Person*> people;
public:
	bool isExist(string &name);
	Person* getPerson(string &name);
	void addPerson(string &uName, string &bName);
	Person* getPBoss(string &bName);
	void set();
	void sort();
	void print(ofstream &out);
	~Group();
};

bool Group::isExist(string &name) {
	vector<Person*>::iterator it;
	for(it=people.begin(); it!=people.end() &&
		!((*it)->getName()==name); ++it)
		;
	if(it!=people.end())
		return true;
	return false;
}

Person* Group::getPerson(string &name) {
	vector<Person*>::iterator it;
	for(it=people.begin(); it!=people.end() &&
		!((*it)->getName()==name); ++it)
		;
	if(it!=people.end())
		return *it;
	cout << "no person whose name is " << name << "." << endl;
	return NULL;
}

void Group::addPerson(string &uName, string &bName) {
	bool uE = isExist(uName), bE = isExist(bName);
	if(uE) {
		if(bE) { // 부하 존재, 보스 존재
			getPerson(uName)->setBoss(getPerson(bName));
		}
		else { // 부하 존재, 보스 존재X
			Person* pPerson = new Person(bName);
			people.push_back(pPerson);
			getPerson(uName)->setBoss(getPerson(bName));
		}
	}
	else {
		if(bE) { // 부하 존재X, 보스 존재
			Person* pPerson = new Person(uName, bName, this);
			people.push_back(pPerson);
		}
		else { // 부하 존재X, 보스 존재X
			Person* pPerson1 = new Person(bName);
			people.push_back(pPerson1);
			Person* pPerson2 = new Person(uName, bName, this);
			people.push_back(pPerson2);
		}
	}
}

Person* Group::getPBoss(string &bName) {
	vector<Person*>::iterator it;
	for(it=people.begin(); it!=people.end() &&
		!((*it)->getName()==bName); ++it)
		;
	if(it!=people.end())
		return *it;
	cout << "no boss." << endl;
	return NULL;
}

Person::Person(string &uName, string &bName, Group* pGroup)
	: name(uName), bName(bName), numOfUnder(0),
	distance(0) {
	Person* pBoss = pGroup->getPBoss(bName);
	this->pBoss = pBoss;
	this->bName = bName;
}

void Group::set() {
	vector<Person*>::iterator it;
	Person* pPerson;

	for(it=people.begin(); it!=people.end(); ++it) {
		int cnt=0;
		pPerson = *it;
		while(!pPerson->isBoss()) {
			pPerson = pPerson->getPBoss();
			pPerson->addNum();
			++cnt;
		}

		(*it)->setDistance(cnt);
	}
}

void Group::sort() {
	std::sort(people.begin(), people.end(),
		[](Person *A, Person *B){
		int numA = A->getNum(), numB = B->getNum();
		int distA = A->getDistance(), distB = B->getDistance();
		if(numA!=numB)
			return numA > numB;
		else if(distA!=distB) {
			return distA < distB;
		}
		else {
			int res = A->getName().compare(B->getName());
			return res<0;
		} 
	});
}

void Group::print(ofstream &out) {
	vector<Person*>::iterator it;
	for(it=people.begin(); it!=people.end(); ++it)
		out << (*it)->getName() << " ";
}

Group::~Group() {
	vector<Person*>::iterator it;
	for(it=people.begin(); it!=people.end(); ++it)
		delete(*it);
}

int main(void)
{
	ifstream inp("org.inp");
	ofstream out("org.out");
	int N, i;
	string uName, bName;
	Group group;

	inp >> N;
	for(i=1; i<N; ++i) {
		inp >> uName >> bName;
		group.addPerson(uName, bName);
	}

	group.set();
	group.sort();

	group.print(out);

	inp.close();
	out.close();
	return 0;
}
