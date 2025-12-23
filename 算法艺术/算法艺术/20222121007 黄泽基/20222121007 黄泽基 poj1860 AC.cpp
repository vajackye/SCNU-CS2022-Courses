#include<iostream>
#include<cstring>

using namespace std;

const int M = 110; //node

int n, m, s, a, b, cnt = 0;
double v;  //注意是double...写错地方了，导致cin一直读不进去下面的a，b...
double r1, c1, r2, c2;
double dis[M << 1]; //value->distance

struct mey
{
	int a, b; //a->b
	double r; //汇率
	double c; //佣金 
} edge[M << 1];//双向

void add(int a, int b, double hl, double yj)
{
	edge[++cnt].a = a;
	edge[cnt].b = b;
	edge[cnt].r = hl;
	edge[cnt].c = yj;
}

//判正环，则：dis_final < dis_start + weight , the n epoch up is right  
bool bellman_ford() {
	memset(dis, 0, sizeof dis);
	dis[s] = v; //到自身为v，即自身原有value，模板为：0.到自身为0，此处需要变换,是正环 
	for (int i = 0; i < n; i++) //n epoch，当第n epoch时，判断是否仍然适用三角不等式（松弛） 
	{
		for (int j = 1; j <= cnt; j++) //每轮迭代所有边,注意是cnt
		{
			int a = edge[j].a, b = edge[j].b;
			double r = edge[j].r, c = edge[j].c;
			if (i == n - 1 && dis[b] < (dis[a] - c) * r)
				return true;
			if (dis[b] < (dis[a] - c) * r)
			{
				dis[b] = (dis[a] - c) * r; //满足汇率公式 
			}
		}
	}
	return false; //无正环 
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> s >> v;

	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> r1 >> c1 >> r2 >> c2;
		add(a, b, r1, c1);
		add(b, a, r2, c2); //双向图 
	}

	int flag = bellman_ford();//spfa
	if (flag)
	{
		cout << "YES";
	}
	else cout << "NO";

	return 0;
}
