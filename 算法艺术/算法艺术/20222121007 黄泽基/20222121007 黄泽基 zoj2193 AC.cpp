#include<bits/stdc++.h>

using namespace std;
int mp[5][5];
int dg[10]; //1~9入度
bool vis[10][10]; //每个点被覆盖了，则标记一下，谁覆盖了其。并dg++
int place[10][2] = {
    
    {-9,-9},// 无用的0号位置
    {0,0},{0,1},{0,2},
    {1,0},{1,1},{1,2},
    {2,0},{2,1},{2,2}
};//1~9的理论占格位置:左上角
int dir[4][2]= {{0,0},{0,1},{1,0},{1,1}}; //1~9的4方位置

bool topo()
{
    int count = 0; // 统计节点
    queue<int> q;
    for(int i = 1; i <= 9; i++)
        if(!dg[i])
        {
            q.push(i);
            count++;
        }
    
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = 1; i <= 9; i++)
        {
            if(i == u) continue;
            if(vis[u][i])
            {
                dg[i]--;
                if(!dg[i]) //不能写在外面，因为有环则会导致：有些入度本来就是0的，会一直0，无限循环
                {
                    q.push(i);
                    count++;
                }
                vis[u][i] = false;
            }

        }
    }

    if(count < 9) return false;
    return true;
}

int main()
{
    //由题目知道，1~9的存放位置固定。则统计原先位置上是否被覆盖，被覆盖则由后来者。则优先级高
    string ss;
    while(cin >> ss)
    {
        if(ss.size() > 5) break;

        //复原
        memset(dg, 0, sizeof dg);
        for(int i = 1; i <= 9; i++)
            for(int j = 1; j <= 9; j++)
                vis[i][j] = false;

        for(int i = 0; i < 4; i ++ )
            for(int j = 0; j < 4; j ++)
                cin >> mp[i][j];
        
        //计算每个点出现的逻辑
        for(int i = 1; i <= 9; i++) //计算1~9出现
        {
            int x = place[i][0], y = place[i][1];
            for(int j = 0; j < 4; j++)
            {
                int nx = x + dir[j][0], ny = y + dir[j][1]; //4角
                if(mp[nx][ny] != i && !vis[mp[nx][ny]][i])
                {
                    vis[mp[nx][ny]][i] = true; //被覆盖
                    dg[i]++; //入度++
                }
            }
        }

        if(topo()) cout<<"THESE WINDOWS ARE CLEAN"<<endl;
        else cout<<"THESE WINDOWS ARE BROKEN"<<endl;
        string end;
        cin >> end;
    }
    return 0;
}
