#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100;
int match[N], mp[N][N];
vector<pair<int, int> > host;
vector<pair<int, int> > dog;

ll get_dis(int x1, int y1, int x2, int y2)
{
	return pow(x1-x2, 2) + pow(y1-y2, 2);
} 

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		host.push_back({x,y});
	}
	
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		dog.push_back({x, y});
	}
	
	int idx = 0;
	int stx = host[idx].first, sty = host[idx++].second;
	for(idx; idx < host.size(); idx++)
	{
		int tox = host[idx].first, toy = host[idx].second;
		
		for(int i = 0; i < dog.size(); i++)
		{
			int dgx = dog[i].first, dgy = dog[i].second;
			double dis = 0;
			dis += sqrt(get_dis(dgx, dgy, stx, sty));
			dis += sqrt(get_dis(dgx, dgy, tox, toy));
			double h_t = sqrt(get_dis(stx, sty, tox, toy));
			if(dis <= h_t*2) {
				mp[idx][i] = 1; //idx和i分别对应vector的内容 
			}
		}
		stx = tox, sty = toy; //更新 
	}
	//打印 
	for(int i = 1; i < host.size(); i++)
	{
		for(int j = 0; j < dog.size(); j++)
		{
			if(mp[i][j])
			{
				printf("(%d,%d) (%d,%d) (%d,%d)\n", host[i-1].first, host[i-1].second, host[i].first, host[i].second, dog[j].first, dog[j].second);
			}
		}
	}
	return 0;
 } 
