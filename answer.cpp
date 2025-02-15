#include<iostream>
#include<cstring>
#include<fstream>
#include<algorithm>
using namespace std;
constexpr int N=205;
int n,m;
int g[N][N];
void work(ifstream& cin,ofstream& cout){
	memset(g,0x3f,sizeof(g));
    cin>>n>>m;
    for(int i=1;i<=n;i++) g[i][i]=0;
    for(int i=0,u,v,w;i<m;i++) cin>>u>>v>>w,g[u][v]=min(g[u][v],w),g[v][u]=min(g[v][u],w);
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
    int ans=-1,minn=1145141;
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=1;j<=n;j++) sum=max(g[i][j],sum);
        if(minn>sum) minn=sum,ans=i;
    }
    cout<<ans<<' '<<minn;
}
int main()
{
    const int n=10;
    for(int i=0;i<n;i++){
        char input[100],output[100];
        sprintf(input,"data%d.in",i+1);
        sprintf(output,"data%d.ans",i+1);
        ifstream in(input);
        ofstream out(output);
        work(in,out);
    }
}
