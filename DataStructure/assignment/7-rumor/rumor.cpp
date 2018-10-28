#include <bits/stdc++.h>
using namespace std;

class Person {
public:
	int id;
	vector< int > link;
public:
	Person(ifstream &inp);
};

Person::Person(ifstream &inp) {
	inp >> this->id;
	int link;
	while(inp>>link && !(link==0)) {
		this->link.push_back(link);
	}
	sort(this->link.begin(), this->link.end());
}

class Listener {
public:
	int id;
	int day;
public:
	Listener(int id, int day)
		: id(id), day(day) {}
};

vector< Person >::iterator getPsIt(vector< Person > &people, int id) {
	vector< Person >::iterator i;
	for(i=people.begin(); i<people.end() &&
		!(i->id==id); ++i)
		;
	return i;
}

bool isRecord(vector< Listener > &record, int id) {
	vector< Listener >::iterator i;
	for(i=record.begin(); i<record.end() &&
		!(id==i->id); ++i)
		;
	if(i<record.end())
		return true;
	else
		return false;
}

void moveQ(queue< int > &from, queue< int > &to) {
	int i = from.front();
	from.pop();
	to.push(i);
}

void moveAndRecord(queue< int > &q, queue< int > &tq,
	vector< Listener > &record, int day) {
	while(q.size() != 0) {
		int id = q.front();
		moveQ(q, tq);
		if(!isRecord(record, id)) {
			Listener l(id, day);
			record.push_back(l);
		}
	}
}

void push(queue< int > &q, queue< int > &tq,
	vector< Person > &people, vector< Listener > &record) {
	while(tq.size() != 0) {
		int id = tq.front();
		tq.pop(); 
		auto it = getPsIt(people, id);
		for(auto i=it->link.begin(); i<it->link.end(); ++i) {
			if(!isRecord(record, *i))
				q.push(*i);
		}
	}
}

void printListener(vector< Listener > &record,
	ofstream &out) {
	for(auto i=record.begin(); i<record.end(); ++i)
		if(i == record.end()-1)
			out << i->id;
		else
			out << i->id << endl;
}

int main()
{
	int N, x, d, i, day=1;
	vector< Person > people;
	queue< int > q, tq;
	vector< Listener > record;
	ifstream inp("rumor.inp");
	ofstream out("rumor.out");
	inp >> N >> x >> d;
	for(i=0; i<N; ++i) {
		Person p(inp);
		people.push_back(p);
	}

	auto it = getPsIt(people, x);
	q.push(it->id);
	for(auto i=it->link.begin(); i<it->link.end(); ++i) {
		q.push(*i);
	}

	while(day <= d) {
		moveAndRecord(q, tq, record, day);
		push(q, tq, people, record);
		++day;
	}

	printListener(record, out);

	inp.close();
	out.close();
	return 0;
}
