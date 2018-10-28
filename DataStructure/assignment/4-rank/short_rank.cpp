#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
typedef vector<int> V;
int n,t,i;
bool f(V a,V b){
	t=a.size();
	i=b.size();
	if(t!=i)
		return t>i;
	else{
		for(i=1;i<t&&a[i]==b[i];++i);
		if(i<t)return a[i]>b[i];
		else return a[0]<b[0];
	}
}
main(){
	ifstream q("rank.inp");
	ofstream w("rank.out");
	q>>n;
	vector<V> d(n);
	for(i=1;i<=n;++i){
		V v(1);
		v[0]=i;
		while(q>>t&&t!=-1)
			v.push_back(t);
		sort(v.begin()+1,v.end());
		d[i-1]=v;
	}
	sort(d.begin(),d.end(),f);
	for(i=0;i<n;++i)
		w<<d[i][0]<<endl;
}
