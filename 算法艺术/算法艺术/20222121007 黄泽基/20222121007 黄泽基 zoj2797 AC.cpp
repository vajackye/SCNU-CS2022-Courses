#include<iostream>
#include<iomanip>
#include<cstring>

using namespace std;
const int N = 110;
int n, m;
int maze[N][N];
double dis[N];
bool vis[N];

double dijkstra()
{
    memset(vis, false, sizeof vis);
    memset(dis, -1, sizeof dis);
    for(int i = 1; i <= n; i++)
        dis[i] = maze[1][i];
    
    vis[1] = true;

    for(int i = 0; i < n - 1; i++)
    {
        //’“◊Ó∂Ã±ﬂ
        int t = -1;
        for(int j = 1; j <= n; j++)
            if(!vis[j] && (t == -1 || dis[t] < dis[j])) //—°±ﬂ°£
                t = j;

        //cout<<t<<" ";
        vis[t] = true;
        
        for(int j = 1; j <= n; j++)
        {
            if(!vis[j] && dis[j] < dis[t] * maze[t][j]/100.0)
            {
                dis[j] = dis[t] * maze[t][j]/100.0;
            }
        }

    }
    return dis[n];
}


int main()
{
    while(cin>>n>>m && n)
    {
        
        int a, b, p;
        memset(maze, -1, sizeof maze);
        for(int i = 1; i <= m; i++)
        {
            cin >> a >> b >> p;
            maze[a][b] = maze[b][a] = max(p, maze[a][b]); //÷ÿ±ﬂ
            //cout<<maze[a][b]<<maze[b][a]<<endl;
        }
        
        cout<<fixed<<setprecision(6)<<dijkstra()<<" percent"<<endl;
    }
    
    return 0;
}
