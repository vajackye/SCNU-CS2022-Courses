#include<bits/stdc++.h>

using namespace std;
const int N = 100;
int x, y;
int cidx, ridx;
int row[N][N], col[N][N];
int Upoint[2505][2505];
int match[2505];
bool vis[2505];

bool find(int now)
{
    for (int j = 1; j <= cidx; j++)
    {
        if (Upoint[now][j] == 1 && !vis[j])
        {
            vis[j] = true;
            if (match[j] == -1 || find(match[j]))
            {
                match[j] = now;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int t;
    cin >> t;
    int id = 1;
    while (t--)
    {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        memset(Upoint, 0, sizeof Upoint);
        memset(match, -1, sizeof match);
        cidx = ridx = 0; //行列最大标号  


        cin >> x >> y;
        char p;
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= y; j++)
            {
                cin >> p;
                if (p == '#') row[i][j] = col[i][j] = -1;
                else if (p == 'o') row[i][j] = col[i][j] = 1;
            }

        //for (int i = 1; i <= x; i++)
        //{
        //    for (int j = 1; j <= y; j++)
        //        cout << row[i][j];
        //    cout << endl;
        //}
        //    
                
        //处理行
        int idx = 0;
        for (int i = 1; i <= x; i++)
        {
            bool adder = false; //判断是否需要递增编号。解决存在：一行/列全是不可放置
            for (int j = 1; j <= y; j++)
            {
                //while (row[i][j] <= 0  && j <= y) j++;
                //++idx;
                //while (row[i][j] > 0 && j <= y)
                //{
                //    row[i][j] = idx;
                //    j++;
                //}
                if (row[i][j] > 0)
                {
                    if (!adder) idx++;
                    adder = true;
                    row[i][j] = idx;
                    ridx = max(idx, ridx);
                }
                else if (row[i][j] < 0) adder = false; //墙壁复原
                //不处理草坪
            }
        }
        //处理列
        idx = 0;
        for (int j = 1; j <= y; j++)
        {
            bool adder = false;
            for (int i = 1; i <= x; i++)
            {
                //while (col[i][j] <= 0 && i <= x) i++;
                //++idx;
                //while (col[i][j] > 0 && i <= x)
                //{
                //    col[i][j] = idx;
                //    i++;
                //}
                if (col[i][j] > 0)
                {
                    if (!adder) idx++;
                    adder = true;
                    col[i][j] = idx;
                    cidx = max(idx, cidx);
                }
                else if (col[i][j] < 0) adder = false; //墙壁复原
            }
        }
        //交点
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= y; j++)
            {
                if (row[i][j] > 0 && col[i][j] > 0)
                    Upoint[row[i][j]][col[i][j]] = 1; //交点
            }

        //匹配
        int res = 0;
        for (int i = 1; i <= ridx; i++)
        {
            memset(vis, false, sizeof vis);
            if (find(i)) res++;
        }
        cout << "Case :" << id++ << endl;
        cout << res << endl;
        //cout << ridx << cidx << endl;
    }
    return 0;
}
