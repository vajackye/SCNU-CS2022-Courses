#include<bits/stdc++.h>

using namespace std;
const int N = 51;  //赣，看清楚题目。最多只有50个空地....否则不能用二分图匹配编号，太大了，会爆
//first method:do the 编号 as row and col，every the interaction is i%2 == 0 && i/2=k, is the ans
//second method: 编号 as every point, if is neighbour, take a line between them
int r, c;
int wall[N][N], a[N][N], match[N];
bool vis[N];
int idx = 1; //标号

//最大只有50个空地
bool check(int i, int j)
{
    return i > 0 && i <= r && j > 0 && j <= c && wall[i][j] != -1;
}

bool find(int x)
{
    for(int i = 1; i < idx; i++)
    {
        if(a[x][i] == 1 && !vis[i])
        {
            vis[i] = true;
            if(match[i] == -1 || find(match[i]))
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
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    while(cin >> r >> c && r && c)
    {
        idx = 1;
        memset(wall, 0, sizeof wall);
        memset(a, 0, sizeof a);
        memset(match, -1, sizeof match);
        int k;
        cin>>k;

        while(k--)
        {
            int i, j;
            cin >> i >> j;
            wall[i][j] = -1;
        }
        //给空地编号
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                if(wall[i][j] == -1) continue;
                wall[i][j] = idx++;
            }
        }
        //链接空地
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                if(wall[i][j] == -1) continue;
                if(check(i, j-1))
                {
                    a[wall[i][j]][wall[i][j-1]] = 1;
                }
                if(check(i-1, j))
                {
                    a[wall[i][j]][wall[i-1][j]] = 1;
                }
                if(check(i,j+1))
                {
                    a[wall[i][j]][wall[i][j+1]] = 1;
                }
                if(check(i+1, j))
                {
                    a[wall[i][j]][wall[i+1][j]] = 1;
                }
            }
        }
        int num = 0;
        for(int i = 1; i < idx; i++)
        {
            memset(vis, false, sizeof vis);
            if(find(i)) num++;
        }
        cout<<num/2<<endl;
    }
    return 0;
}
