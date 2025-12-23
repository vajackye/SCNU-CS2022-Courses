#include<iostream>
#include<vector>
#include<cstring>

using namespace std;
const int N = 1010;
int A_B[N][N];
int n;
int match[N];
bool vis[N];

bool find(int x)
{
    //递归找所有其匹配
    for(int i = 0; i < n; i++)
    {
        //if(x == i) continue;
        if(!vis[i] && A_B[x][i]) //其配对对象未被访问
        {
            vis[i] = true; //配对。
            if(match[i] == -1 || find(match[i])) //如果i未被配对或者，为其找新的对象。
            {
                match[i] = x;   
                return true;
            }
        }
    }
    return false;
}


//匈牙利：最大匹配数==最小点覆盖（匹配点/2)==最大独立集（点数-最小覆盖点）
int main()
{
    int cnt = 0;
    while(scanf("%d", &n) != EOF)
    {
        memset(match, -1, sizeof match);
        memset(vis, false, sizeof vis);
        memset(A_B, 0, sizeof A_B); 
        int idx, num;
        for(int i = 0; i < n; i++)
        {
            scanf("%d: (%d)", &idx, &num);
            for(int j = 0; j < num; j++)
            {
                int to;
                scanf("%d", &to);
                A_B[idx][to] = 1;
            }
        }

        //求最大匹配
        int res = 0;
        for(int i = 0; i < n; i++)
        {
            memset(vis, false, sizeof vis);
            if(find(i)) res++; //新匹配成功
        }
        if(!cnt)
            printf("%d", n - res/2); //本题匹配会重复计算。
        else printf("\n%d", n - res/2);
        cnt++;
    }
}
