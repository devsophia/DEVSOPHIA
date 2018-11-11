#include <bits/stdc++.h>
using namespace std;

class User {
private:
	int id;
	int start, end;
public:
	User(int id, int start, int end)
		: id(id), start(start), end(end)
		{}
	const int getId() const {
		return this->id;
	}
	const int getEnd() const {
		return this->end;
	}
	bool isIncluding(int q) const {
		if(this->start <= q)
			return true;
		return false;
	}
};

vector< int > getIncludings(list< User >::iterator it,
	list< User > &Users, int q) {
	vector< int > includings;
	while(it != Users.end()) {
		if(it->isIncluding(q)) 
			includings.push_back(it->getId());
		advance(it, 1);
	}
	return includings;
}

void print(vector< int > includings,
	ofstream &out) {
	if(includings.size()==0)
		out << "0" << endl;
	else {
		auto it = includings.begin();
		while(it != includings.end()) {
			out << *it << " ";
			++it;
		}
		out << endl;
	}
}

int main(void)
{
	int N, K, i;
	int id, start, end;
	int Q[100];
	list< User > Users;
	list< User >::iterator it;
	ifstream inp("log.inp");
	ofstream out("log.out");

	inp >> N >> K;
	for(i=0; i<N; ++i) {
		inp >> id >> start >> end;
		User U(id, start, end);
		Users.push_back(U);
	}
	for(i=0; i<K; ++i) {
		inp >> id;
		Q[i] = id;
	}

	Users.sort(
		[](User &A, User &B) {
			return A.getEnd() < B.getEnd();
		}
	);

	it = Users.begin();
	for(i=0; i<K; ++i) {
		vector< int > includings;
		while(it->getEnd() < Q[i] &&
			it != Users.end())
			advance(it, 1);
		includings = getIncludings(it, Users, Q[i]);
		sort(includings.begin(), includings.end());
		print(includings, out);
	}

	inp.close();
	out.close();
	return 0;
}
