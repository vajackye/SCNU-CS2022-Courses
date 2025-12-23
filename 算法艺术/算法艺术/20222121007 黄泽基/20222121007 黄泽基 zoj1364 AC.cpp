#include<iostream>
#include<cstring>

using namespace std;
const int N = 110;
int i, x, y, n, m, k;
int a[N][N]; //x, y
int match[N]; //y match x
bool vis[N];

//求用最少点覆盖最大的机器。也就是求最大匹配（求用最少点覆盖最大的机器
//覆盖所有边）
bool find(int x)
{
    for(int i = 1; i <= m; i++)
    {
        //int tmp;
        if(a[x][i] == 1 && !vis[i])
        {
            vis[i] = true;
            if(match[i] == 0 || find(match[i]))
            {
                match[i] = x;
                return true;
            }    
        }
    }
    return false;
}

int main()
{
    while(cin >> n >> m >> k && n != 0 && m != 0)
    {
        memset(match, 0, sizeof match);
        memset(vis, false, sizeof vis);
        memset(a, 0, sizeof a);
        while(k--)
        {
            cin >> i >> x >> y;
            a[x][y] = 1;
        }

        int num = 0;
        for(int i = 1; i <= n; i ++)
        {
            memset(vis, false, sizeof vis);
            if(find(i)) num ++;
        }
        cout<<num<<endl;
    }
    return 0;
}
