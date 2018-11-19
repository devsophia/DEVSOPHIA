#include <bits/stdc++.h>
using namespace std;

// deck를 A, B로 나누고 하나씩 번갈아가며 다시 deck에 섞어넣는 함수
void Shuffle(list< int > &deck) {
	int mid;
	list< int > A;
	list< int > B;
	list< int >::iterator it;

	//ceil(N/2) 계산
	mid = ceil((double)deck.size()/2.0);
	it = deck.begin();
	advance(it, mid);

	//deck를 A와 B로 나누기
	A.splice(A.begin(), deck, deck.begin(), it);
	B.splice(B.begin(), deck, deck.begin(), deck.end());

	//하나씩 번갈아가며 섞어넣기
	while(A.size()>0 || B.size()>0) {
		if(A.size()>0)
			deck.splice(deck.end(), A, A.begin());
		if(B.size()>0)
			deck.splice(deck.end(), B, B.begin());
	}
}

// beg번째부터 end번째까지 cut작업하는 함수
void Cut(list< int > &deck, int beg, int end) {
	list< int >::iterator it1, it2;

	// splice작업을 위한 it1, it2 설정
	it1 = deck.begin();
	it2 = deck.begin();
	advance(it1, beg-1);
	advance(it2, end);

	deck.splice(deck.end(), deck, it1, it2);
}

int main(void)
{
	int N, K, i;
	list< int > deck;
	list< int >::iterator it;
	string inst;

	ifstream inp("card.inp");
	ofstream out("card.out");

	inp >> N >> K;

	// 초기 deck 구성
	for(i=0; i<N; ++i)
		deck.push_back(i+1);

	// 작업 수행
	for(i=0; i<K; ++i) {
		inp >> inst;

		if(inst == "Shuffle") { // Shuffle인 경우
			Shuffle(deck);
		}
		else if(inst == "Cut"){ // Cut인 경우
			int beg, end;
			inp >> beg >> end;
			Cut(deck, beg, end);
		}
		else
			out << "No Such Instruction." << endl;
	}

	// 출력을 위한 floor(N/2)계산
	it = deck.begin();
	advance(it, deck.size()/2-1);

	out << deck.front() << " "
		<< *it << " "
		<< deck.back();

	inp.close();
	out.close();
	return 0;
}
