#include<iostream>
#include<cstring>

using namespace std;
const int N = 1010;
int f[N][N]; //i,j

int dfs(int fir, int sec, string a, string b)
{

    if(fir < 0 || sec < 0) return 0; //不能是!fir||!sec,因为有一部分会没算到：f[0][k] = max(f[-1][k],...，这就会导致部分结果不对
    if(f[fir][sec] != -1) return f[fir][sec]; //记忆化搜索，剪枝
    if(a[fir] == b[sec]) return f[fir][sec] = dfs(fir-1, sec - 1, a, b) + 1;
    else
        return f[fir][sec] = max(dfs(fir, sec - 1, a, b), dfs(fir - 1, sec, a, b));
}

int main()
{
    string a, b;
    while(cin >> a >> b)
    {
        memset(f, -1, sizeof f);
        int MI = a.size(), MJ = b.size();
        dfs(MI-1, MJ-1, a, b);
        cout<<f[MI-1][MJ-1]<<endl;
    }
    return 0;
}
