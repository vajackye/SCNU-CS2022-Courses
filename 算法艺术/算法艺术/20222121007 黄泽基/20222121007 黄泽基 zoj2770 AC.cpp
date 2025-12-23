#include<bits/stdc++.h>

using namespace std;
const int N = 1010, inf = 0x3f3f3f3f;
int n, m, idx;
int s[N], dis[N]; //s为前缀和，求营地最大总数，dis为最短路径。
struct ss
{
	int u, v, w;
} mp[N*22];

void add(int u, int v, int w)
{
	mp[idx].u = u, mp[idx].v = v, mp[idx++].w = w;
}

bool bellman_ford()
{
	memset(dis, 0x3f, sizeof dis);//虚拟源点到其他任何点的距离。
	//for (int i = 0; i < n; i++) dis[i] = inf;

	//dis[0] = dis[n] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < idx; j++)
		{
			int u = mp[j].u, v = mp[j].v, w = mp[j].w;
			if (dis[v] > dis[u] + w) 
			{
				dis[v] = dis[u] + w;
			}
		}
	}

	for (int j = 0; j < idx; j++)
	{
		int u = mp[j].u, v = mp[j].v, w = mp[j].w;
		if (dis[v]>dis[u] + w) 
		{
			return false;
		}
	}

	return true;
}

int main()
{
	while (cin >> n >> m)
	{
		idx = 0; //复原边集数组
		for (int i = 1; i <= n; i++)
		{
			int c;
			cin >> c;
			add(i - 1, i, c);//所有边约束条件，其实就是边value
			add(i, i - 1, 0);
			s[i] = s[i - 1] + c; //前缀和
		}

		for (int t = 0; t < m; t++)
		{
			int i, j, k;
			cin >> i >> j >> k;
			add(j, i - 1, -k);//最少人数
			add(i - 1, j, s[j] - s[i - 1]);//最多人数
		}
		if (bellman_ford()) cout <<dis[n]-dis[0]<< endl;
		else cout << "Bad Estimations\n";
	}
	return 0;
}
