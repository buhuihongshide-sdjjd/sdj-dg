#include<iostream>
#include<cstring>
#include<fstream>
#include<algorithm>
using namespace std;
constexpr int N=205;
int n,m;
int g[N][N];
void work(ifstream& cin,ofstream& cout){
	int N, Q;
    cin >> N >> Q;
    // 分配大小为 (N+2) x (N+2) 的二维数组，防止更新时越界
    int size = N + 2;
    vector<vector<long long>> diffC(size, vector<long long>(size, 0));
    vector<vector<long long>> diffI(size, vector<long long>(size, 0));
    vector<vector<long long>> diffJ(size, vector<long long>(size, 0));
    
    for (int k = 0; k < Q; k++){
        int x, y, d;
        cin >> x >> y >> d;
        int x2 = x + d - 1, y2 = y + d - 1;
        long long c = 1LL - 2LL * x - 2LL * y; // 常数项
        long long a = 2, b = 2;                // i和j对应的系数
 
        // 更新 diffC
        diffC[x][y]       += c;
        diffC[x][y2 + 1]  -= c;
        diffC[x2 + 1][y]  -= c;
        diffC[x2 + 1][y2 + 1] += c;
 
        // 更新 diffI
        diffI[x][y]       += a;
        diffI[x][y2 + 1]  -= a;
        diffI[x2 + 1][y]  -= a;
        diffI[x2 + 1][y2 + 1] += a;
 
        // 更新 diffJ
        diffJ[x][y]       += b;
        diffJ[x][y2 + 1]  -= b;
        diffJ[x2 + 1][y]  -= b;
        diffJ[x2 + 1][y2 + 1] += b;
    }
    
    // 计算二维前缀和，注意 i,j 从1开始
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            diffC[i][j] += diffC[i-1][j] + diffC[i][j-1] - diffC[i-1][j-1];
            diffI[i][j] += diffI[i-1][j] + diffI[i][j-1] - diffI[i-1][j-1];
            diffJ[i][j] += diffJ[i-1][j] + diffJ[i][j-1] - diffJ[i-1][j-1];
        }
    }
    
    // 计算最终结果并输出
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            long long val = diffC[i][j] + diffI[i][j] * i + diffJ[i][j] * j;
            cout << val << " ";
        }
        cout << "\n";
    }
}
int main()
{
    const int n=5;
    for(int i=0;i<n;i++){
        char input[100],output[100];
        sprintf(input,"data%d.in",i+1);
        sprintf(output,"data%d.ans",i+1);
        ifstream in(input);
        ofstream out(output);
        work(in,out);
    }
}
