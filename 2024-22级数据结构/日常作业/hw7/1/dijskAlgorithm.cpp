#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<functional>
using namespace std;

struct Compare {
	bool operator()(const pair<int, pair<int, int>>& p1, const pair<int, pair<int, int>>& p2) {
		// 自定义比较函数，按照升序排列
		return p1.first > p2.first;
	}
};


//并查集部分 
class UCF
{
	int* parent;
	int size;
public:
	UCF(int len) :size(len) { parent = new int[len]; }
	~UCF() { delete[]parent; }
	void init()
	{
		for (int i = 0; i < size; i++)
			parent[i] = i;
	}

	int find(int x)
	{
		return x == parent[x] ? x : find(parent[x]);
	}

	void merge(int x, int y)
	{
		x = find(x); y = find(y);
		if (x != y)parent[x] = parent[y];
	}
};


//卡鲁斯卡尔算法 
int kruskal(UCF& check, int** GraphMa, int r)
{
	int count = 0; //够r-1，提前终止信号。
	check.init();
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Compare> q;
	for (int i = 0; i < r; i++)
	{
		for (int j = i + 1; j < r; j++)
		{
			if (GraphMa[i][j])
				q.push({ GraphMa[i][j],{i,j } });
			else continue;
		}
	}
	int weight = 0;
	while (count < r - 1 && !q.empty())
	{
		auto elem = q.top();
		q.pop();
		if (check.find(elem.second.first) != check.find(elem.second.second))
		{
			count++;
			check.merge(elem.second.first, elem.second.second);
			cout << elem.second.first << "--" << elem.second.second << "  W:" << elem.first << endl;
			weight += elem.first;
		}
	}
	if (count != r - 1)return 0;
	return weight;
}

//普利姆算法 
int prim(int** GraphMa, int r)
{
	vector<bool> inMST(r, false); //判断该顶点是否在最小生成树中（第一组）
	vector<int> key(r, INT_MAX); //存储顶点的最小边权值
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
	int count = 0; //记录顶点个数
	int weight = 0;

	//从第一个顶点开始
	q.push({ 0,0 });//key,index
	key[0] = 0;

	while (!q.empty() && count < r)
	{
		int u = q.top().second;
		int w = q.top().first;
		q.pop();

		if (inMST[u]) continue;//该点已存在最下生成树中

		inMST[u] = true;
		weight += w;
		count++;
		cout << "顶点" << u << "加入最小生成树 W:" << w << endl;
		for (int v = 0; v < r; v++)
		{
			if (GraphMa[u][v] && !inMST[v] && GraphMa[u][v] < key[v])//非环，v不在树中，边小于值
			{
				key[v] = GraphMa[u][v];
				q.push({ key[v],v });
			}
		}
	}
	if (count != r)return 0;
	return weight;
}

//初始化邻接矩阵 
void getGraphNode(int r, int c, int**& GraphMa)
{
	GraphMa = new int* [r];
	for (int i = 0; i < r; i++)
		GraphMa[i] = new int[c];

	return;
}

int main()
{
	int r, c;
	cout << "请输入行数列数：" << endl;
	while (cin >> r >> c && r != -1 && c != -1)
	{
		if (r == 0 || c == 0)
		{
			cout << "结果为0" << endl;
			cout << "请再次输入行数和列数" << endl;
			continue;
		}
		//创建邻接矩阵 
		int** GraphMa;
		getGraphNode(r, c, GraphMa);

		//初始化邻接矩阵
		cout << "请依次输入权值:" << endl;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				cin >> GraphMa[i][j];

		//初始化并查集 
		UCF check(r);
		//kruskal算法
		cout << "Kruskal算法：" << endl;
		int weight = kruskal(check, GraphMa, r);
		if (weight) cout << "总权值为：" << weight << endl;
		else cout << "无法构成最小生成树！" << endl;


		cout << endl;


		//prim算法
		cout << "Prim算法：" << endl;
		int ww = prim(GraphMa, r);
		if (ww) cout << "总权值为：" << ww << endl;
		else cout << "无法构成最小生成树！" << endl;
		//清空数组
		for (int i = 0; i < r; i++)
			delete[]GraphMa[i];
		delete[]GraphMa;
		cout << "请再次输入行数和列数" << endl;
	}
	system("pause");
	return 0;
}