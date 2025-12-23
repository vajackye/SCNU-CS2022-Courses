#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
double mp[210][210], dis[N];
int t;
bool vis[210][210];

struct s
{
	int x, y;
} sto[N];

double sqt(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void dijkstra()
{
	for(int k = 1; k <= t; k++)
		for (int i = 1; i <= t; i++)
		{
			for (int j = 1; j <= t; j++)
			{
				mp[i][j] = min(mp[i][j], max(mp[i][k], mp[k][j])); //找所有最大跳跃的最小值
			}
		}
}

int main()
{
	int idx = 1;
	while (scanf("%d", &t) && t)
	{
		memset(dis, 0x3f, sizeof dis);
		memset(vis, false, sizeof vis);
		for (int i = 1; i <= t; i++) //记录所有节点距离 
		{
			scanf("%d%d", &sto[i].x, &sto[i].y);
		}

		//求所有节点距离 
		for (int i = 1; i <= t; i++)
		{
			for (int j = 1; j <= t; j++)
			{
				mp[i][j] = sqt(sto[i].x, sto[i].y, sto[j].x, sto[j].y);
				mp[j][i] = mp[i][j];
			}
		}

		// for (int i = 1; i <= t; i++)
		// {
		// 	for (int j = 1; j <= t; j++)
		// 	{
		// 		cout << mp[i][j] << " ";
		// 	}
		// 	cout << endl;
		// }

		dijkstra();
		printf("Scenario #%d\n", idx++);
		printf("Frog Distance = %.3f\n\n", mp[1][2]);
	}
	return 0;
}
