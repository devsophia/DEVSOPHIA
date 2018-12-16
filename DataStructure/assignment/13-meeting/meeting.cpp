#include <bits/stdc++.h>
using namespace std;

class Graph;

class Vertex {
friend class Graph;
private:
	string id;
	list<Vertex*> adj; // has pointers of each adjacent vertexes
	map<string, int> time; // key : string of starting point, value : time from starting point
	int maxTime; // Biggest one among time
	bool isVisited;
public:
	Vertex(string id) : id(id),
		isVisited(false), maxTime(0) {}
};

class Graph {
private:
	int N;
	vector<Vertex*> vertexes; // has pointers of all Vertexes
	vector<string> starters; // has string of starter vertex
public:
	// make Vertexes and Graph
	Graph(ifstream &inp);
	// get pointer of Vertex whose id is id
	Vertex* getPVertex(string id);
	// set all isVisited false
	void reset();
	// BFS traverse, set time of each vertexes, set maxTime, sort by maxTime
	void traverse();
	// print according to form
	void print(ofstream &out);
	~Graph();
};
Graph::Graph(ifstream &inp) {
	int N;
	string id1, id2, id3;

	inp >> N;
	inp >> id1 >> id2 >> id3;
	this->N = N;
	starters.push_back(id1);
	starters.push_back(id2);
	starters.push_back(id3);

	while(N--) {
		Vertex *pVertex, *pAdj;
		string id;
		inp >> id;
		if(!(pVertex = getPVertex(id))) {
			pVertex = new Vertex(id);
			vertexes.push_back(pVertex);
		}
		while(inp >> id && id != "$") {
			if(!(pAdj = getPVertex(id))) {
				pAdj = new Vertex(id);
				vertexes.push_back(pAdj);
			}
			pVertex->adj.push_back(pAdj);
		}
	}

	for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
		for(auto it2=starters.begin(); it2!=starters.end(); ++it2)
			(*it)->time.insert(pair<string, int>((*it2), 0));
	}
}
Vertex* Graph::getPVertex(string id) {
	vector<Vertex*>::iterator it;
	for(it=vertexes.begin(); it!=vertexes.end() &&
		!((*it)->id==id); ++it) ;
	if(it!=vertexes.end())
		return *it;
	return NULL;
}
void Graph::reset() {
	for(auto it=vertexes.begin(); it!=vertexes.end();
		++it) (*it)->isVisited = false;
}
void Graph::traverse() {
	// traverse and set times(from starting vertexes) of each vertexes.
	for(auto it=starters.begin(); it!=starters.end();
		++it) {
		string id = *it;
		Vertex *starter = getPVertex(id), *pVertex;
		queue<Vertex*> q;

		q.push(starter);
		starter->isVisited = true;
		pVertex = q.front();
		q.pop();
		for(auto it2=pVertex->adj.begin(); it2!=pVertex->adj.end(); ++it2) {
			q.push(*it2);
			(*it2)->isVisited = true;
		}

		while(q.size()!=0) {
			pVertex = q.front();
			q.pop();
			pVertex->time[id] += 1;
			for(auto it3=pVertex->adj.begin();
				it3!=pVertex->adj.end(); ++it3) {
				if(!((*it3)->isVisited)) {
					(*it3)->time[id] = pVertex->time[id] + 2;
					q.push(*it3);
					(*it3)->isVisited = true;
				}
			}
		}
		reset();
	}
	// set maxTime of each vertexes
	for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
		int max=0;
		for(auto it2=(*it)->time.begin(); it2!=(*it)->time.end(); ++it2)
			max = (it2->second > max) ? it2->second : max;
		(*it)->maxTime = max;
	}
	// sort vertexes according to maxTime and order of its id
	sort(vertexes.begin(), vertexes.end(), [](Vertex *A, Vertex *B){
		if(A->maxTime != B->maxTime)
			return A->maxTime < B->maxTime;
		else
			return A->id.compare(B->id) < 0;
	});
}
void Graph::print(ofstream &out) {
	out << vertexes[0]->id << endl;
	out << vertexes[0]->maxTime;
}
Graph::~Graph() {
	for(auto it=vertexes.begin(); it!=vertexes.end(); ++it)
		delete(*it);
}

int main(void)
{
	ifstream inp("1.inp");
	ofstream out("meeting.out");
	Graph graph(inp);
	graph.traverse();
	graph.print(out);

	inp.close();
	out.close();
	return 0;
}
