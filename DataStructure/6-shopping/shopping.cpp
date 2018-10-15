#include <bits/stdc++.h>
using namespace std;

class Customer {
private:
	int id;
	int w;
public:
	Customer(int id, int w);
	int getId(void) const {
		return this->id;
	}
	int getW(void) const {
		return this->w;
	}
	void setW(void) {
		this->w -= 1;
	}
};

Customer::Customer(int id, int w)
	: id(id), w(w) {}

class Casher {
private:
	int id;
	int restime;
	queue< Customer > waiting;
public:
	Casher(int id);
	void customerIn(Customer &ct);
	int getRestime(void) const {
		return this->restime;
	}
	int getId(void) const {
		return this->id;
	}
	void timePass(vector< int > &record);
};

Casher::Casher(int id)
	: id(id), restime(0) {}

void Casher::customerIn(Customer &ct) {
	this->waiting.push(ct);
	this->restime += ct.getW();
}

void Casher::timePass(vector< int > &record) {
	if(this->waiting.size() > 0 && this->getRestime() > 0) {
		Customer &ct = this->waiting.front();
		if(ct.getW() > 0) {
			ct.setW();
			this->restime -= 1 ;
		}
		if(ct.getW() == 0) {
			record.push_back(ct.getId());
			this->waiting.pop();
		}
	}
}

bool casherAlign(Casher &a, Casher &b) {
	if(a.getRestime() == b.getRestime())
		return a.getId() < b.getId();
	else
		return a.getRestime() < b.getRestime();
}

bool casherAlign2(Casher &a, Casher &b) {
	return a.getId() > b.getId();
}

void timePass(vector< Casher > &Cashers, vector< int> &record, int k) {
	for(int i=0; i<k; ++i)
		Cashers[i].timePass(record);
}

bool isEmpty(vector< Casher > &Cashers, int k) {
	int i;
	for(i=0; i<k; ++i)
		if(!(Cashers[i].getRestime() == 0))
			return false;
	return true;
}

int main()
{
	int N, k, i;
	vector< Customer > Customers;
	vector< Casher > Cashers;
	vector< int > record;
	ifstream inp("shopping.inp");
	ofstream out("shopping.out");

	inp >> N >> k;
	for(i=0; i<N; ++i) {
		int id, w;
		inp >> id >> w;
		Customer ct(id, w);
		Customers.push_back(ct);
	}

	for(i=0; i<k; ++i) {
		Casher cs(i);
		Cashers.push_back(cs);
	}

	// 고객 줄서기
	for(i=0; i<N; ++i) {
		sort(Cashers.begin(), Cashers.end(), casherAlign);
		Cashers[0].customerIn(Customers[i]);
	}

	sort(Cashers.begin(), Cashers.end(), casherAlign2);
	while(!isEmpty(Cashers, k)) {
		timePass(Cashers, record, k);
	}

	for(auto it=record.begin(); it<record.end(); ++it)
		out << *it << endl;

	inp.close();
	out.close();
	return 0;
}
