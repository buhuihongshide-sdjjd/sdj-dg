#include<iostream>
#include<fstream>
#include<random>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
mt19937 gen;
void reload(){
	random_device rd;
	unsigned int new_seed=rd();
	gen.seed(new_seed);
}
int rd(int l,int r){
	int diff=r-l+1;
	int ret=gen()%diff;
	ret+=l;
	return ret;
}
void work(ofstream& cout){
	int n=150+rd(0,50);
	int m=rd(n+1,1e5);
	cout<<n<<' '<<m<<'\n';
	map<pair<int,int>,int> mp;
	while(m--){
		int s=rd(1,n);
		int t=rd(1,n);
		while(t==s) t=rd(1,n);
		if(++mp[make_pair(min(s,t),max(s,t))]>5000){
			m++;
			continue;
		}
		cout<<s<<' '<<t<<' '<<rd(1,9999)<<'\n';
	}
}
int main()
{
	const int n=10;
	for(int i=0;i<n;i++){
		char input[100];
		sprintf(input,"data%d.in",i+1);
		ofstream out(input);
		reload();
		work(out);
	}
}
