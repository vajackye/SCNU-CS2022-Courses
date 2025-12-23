#include<bits/stdc++.h>

using namespace std;
const int N = 5;
int n;
int mp[N][N], row[N][N], col[N][N]; 
int pic[20][20]; //最大为16=idx
int match[20];
bool vis[20];
int cidx, ridx;

bool find(int x)
{
    for(int i = 1; i <= cidx; i++)
    {
        //是pic，不是mp，不要搞混了。
        if(pic[x][i] && !vis[i]) //未访问且无格挡
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
    while(cin >> n && n)
    {
        memset(mp, 0, sizeof mp);
        memset(pic, 0, sizeof pic);
        memset(match, -1, sizeof match);
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);

        cidx = ridx = 0;
        
        for(int i = 1; i <= n; i++)
        {
            char p;
            for(int j = 1; j <= n; j++)
            {
                cin >> p;
                if(p == 'X') mp[i][j] = row[i][j] = col[i][j] = -1;
            }
        }

        //行处理
        int idx = 0;//勿定义为全局的，若如样例n=2:xx .x，if idx, 则为1为max，多遍历
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                //边界为==n
                while(mp[i][j] == -1 && j <= n) j++; //跳过障碍
                idx++;
                while(mp[i][j] != -1 && j <= n) 
                {
                    row[i][j] = idx;
                    ridx = max(ridx, idx); //样例n=2，xx .x不会更新ridx
                    j++;
                }
            }
        }
        //列处理
        idx = 0; 
        for(int j = 1; j <= n; j++)
        {
            for(int i = 1; i <= n; i++)
            {
                while(mp[i][j] == -1 && i <= n) i++; //跳过障碍
                idx++;
                while(mp[i][j] != -1 && i <= n) 
                {
                    col[i][j] = idx;
                    cidx = max(cidx, idx); //样例n=2，xx .x不会更新cidx
                    i++;
                }
            }
        }

        //交叉
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
                if(mp[i][j] != -1)
                    pic[row[i][j]][col[i][j]] = 1; //交点标记
        }

        int res = 0;
        //开始匹配
        for(int i = 1; i <= ridx; i++)
        {
            memset(vis, false, sizeof vis);
            if(find(i)) res++;
        }
        //不需要除2
        cout<<res<<endl;
    }
    return 0;
}


