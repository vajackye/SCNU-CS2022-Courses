#include<iostream>
#include<utility>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

int dir[8][2] = {{1,2},{2,1},{2,-1},
                {1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};
int vis[10][10];
int maze[10][10];

bool check(int x, int y)
{
    return x > 0 && x < 9 && y > 0 && y < 9;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    string a, b;
    vector<pair<string,string>> place;
    while(cin >> a >> b)
    {
        maze[a[0]-'a'+1][a[1]-'0'] = 1;
        maze[b[0]-'a'+1][b[1]-'0'] = 1;
        place.push_back({a, b});
    }

    int siz = place.size();
    for(int i = 0; i < siz; i++)
    {
        queue<pair<pair<int, int> ,int>> q;
        memset(vis, false, sizeof vis);
        auto c = place[i];
        q.push({{c.first[0]-'a'+1, c.first[1]-'0'},0});
        vis[c.first[0]-'a'+1][c.first[1]-'0'] = true;
        while(q.size())
        {
            int x = q.front().first.first, y = q.front().first.second;
            int step = q.front().second;
            q.pop();
            if(x == c.second[0]-'a'+1 && y == c.second[1]-'0')
            {
                cout<<"To get from "<<c.first<<" to "<< c.second<<" takes "<<step<<" knight moves."<<endl; 
                break;
            }
            for(int i = 0; i < 8; i++)
            {
                int sx = x+dir[i][0], sy = y+dir[i][1];
                if(check(sx, sy) && !vis[sx][sy]) {
                    q.push({{sx, sy}, step + 1});
                    vis[sx][sy] = true;
                }
            }
        }
    }
    
    return 0;
}

