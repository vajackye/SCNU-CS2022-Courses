#include<bits/stdc++.h>

using namespace std;
const int N = 5;
int n;
int mp[N][N], row[N][N], col[N][N]; 
int pic[20][20]; //最
int match[20];
bool vis[20];
int cidx, ridx;

bool find(int x)
{
    for(int i = 1; i <= cidx; i++)
    {
        if(pic[x][i] && !vis[i]) 
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

        
        int idx = 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
  
                while(mp[i][j] == -1 && j <= n) j++; 
                idx++;
                while(mp[i][j] != -1 && j <= n) 
                {
                    row[i][j] = idx;
                    ridx = max(ridx, idx); 
                    j++;
                }
            }
        }
        idx = 0; 
        for(int j = 1; j <= n; j++)
        {
            for(int i = 1; i <= n; i++)
            {
                while(mp[i][j] == -1 && i <= n) i++; 
                idx++;
                while(mp[i][j] != -1 && i <= n) 
                {
                    col[i][j] = idx;
                    cidx = max(cidx, idx); 
                    i++;
                }
            }
        }

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
                if(mp[i][j] != -1)
                    pic[row[i][j]][col[i][j]] = 1; 
        }

        int res = 0;
        for(int i = 1; i <= ridx; i++)
        {
            memset(vis, false, sizeof vis);
            if(find(i)) res++;
        }
        cout<<res<<endl;
        
        for(int i = 0; i < 20; i++)
        {
        	if(match[i] > 0)
        	{
				for(int l = 0; l <= 4; l++)
					for(int e = 0; e<=4; e++)
					//改正后AC点，row和col写反了。 
						if(row[l][e]==match[i] && col[l][e]==i)
						{
							cout<<"("<<l-1<<","<<e-1<<")"<<endl;
						}
				
				}
			}
	}
    return 0;
}


