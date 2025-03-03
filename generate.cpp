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
	int n=1000,q=1e6;
	cout<<n<<' '<<q<<'\n';
	while(q--){
		int x=rd(1,n);
		int y=rd(1,n);
		int mx=min(n-x+1,n-y+1);
		int d=rd(1,mx);
		cout<<x<<' '<<y<<' '<<d<<'\n';
	}
}
int main()
{
	const int n=5;
	for(int i=0;i<n;i++){
		char input[100];
		sprintf(input,"data%d.in",i+1);
		ofstream out(input);
		reload();
		work(out);
	}
}
