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
	//写下所有1->其他点的距离
	for (int i = 1; i <= t; i++)
		dis[i] = mp[1][i];

	dis[1] = 0; //到自己的距离
	vis[1][1] = true;
	for (int i = 1; i < t; i++) //n-1趟 
	{
		int pos;
		double midis = 1e7;//找该点到其他点最短的距离 ，确保："最小的"最大
		for (int k = 1; k <= t; k++) //找最小
		{
			if (!vis[k][k] && (dis[k] < midis))
			{
				pos = k;
				midis = dis[k];
			}
		}
		vis[pos][pos] = true; //遍历
		for (int k = 1; k <= t; k++) //中转
		{
			if (!vis[k][k] && (dis[k] > mp[pos][k])) //原理是：取最小的即可。我们是一段一段取。所以可以这样
				dis[k] = max(midis ,mp[pos][k]); //取最短的段。
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

//		for (int i = 1; i <= t; i++)
//		{
//			for (int j = 1; j <= t; j++)
//			{
//				cout << mp[i][j] << " ";
//			}
//			cout << endl;
//		}

		dijkstra();
		printf("Scenario #%d\n", idx++);
		printf("Frog Distance = %.3f\n\n", dis[2]);
	}
	return 0;
}
