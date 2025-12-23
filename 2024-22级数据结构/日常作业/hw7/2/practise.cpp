#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<functional>
using namespace std;

void dijkstra(int v0, int n, long long dis[], long long** GraphMatrix)
{
	for (int i = 0; i < n; i++)
		dis[i] = GraphMatrix[v0][i];
	GraphMatrix[v0][v0] = 1;  //用于表示访问过该点。
	for (int i = 0; i < n - 1; i++)  //完成n-1次,即n-1个其余点。 
	{
		//找距离源点s最小距离点 
		int min = INT_MAX;
		int pos = 0; //记录最小距离点的index 
		for (int k = 0; k < n; k++)
		{
			if (GraphMatrix[k][k] == 0 && dis[k] < min)
			{
				pos = k;
				min = dis[k];//更新最短距离 
			}
		}
		GraphMatrix[pos][pos] = 1;//获取最小距离，使其遍历过,接下来n-l轮不再遍历其
		for (int j = 0; j < n; j++)
		{
			if (GraphMatrix[j][j] == 0 && GraphMatrix[pos][j] + min < dis[j])//即该点到其他任意点距离短于源点到距离。更新源点到最短距离（路径）
				dis[j] = GraphMatrix[pos][j] + min;
		}
	}

}

void display(int v0, int n, long long dis[])
{
	cout << "源点" << v0 << "到其他任意点的距离为：" << endl;
	for (int i = 0; i < n; i++)
	{
		if (i == v0)
			continue;
		if (dis[i] == INT_MAX)
			cout << "无法抵达" << i << "点" << "  ";
		else 
			cout << dis[i] << " ";
	}

}

void init(int r, int c, long long**& GraphMatrix)
{
	GraphMatrix = new long long* [r];
	for (int i = 0; i < r; i++)
		GraphMatrix[i] = new long long[c];
}

int main()
{

	int r, c;
	cout << "请输入行数和列数:" << endl;
	while (cin >> r >> c && c != -1 && r != -1)
	{
		if (r == 0 || c == 0)
		{
			cout << "0!" << endl;
			continue;
		}

		//初始化阶段 
		long long ** GraphMatrix; //邻接矩阵 
		long long * dis;//距离表 
		init(r, c, GraphMatrix);
		dis = new long long[r];

		//输入结点：
		cout << "请输入有向节点间距离，无穷大请用：-1" << endl;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
			{
				cin >> GraphMatrix[i][j];
				if (GraphMatrix[i][j] == -1)
					GraphMatrix[i][j] = INT_MAX;
			}


		cout << "请输入起始源点：" << endl;
		int v0;
		cin >> v0;
		dijkstra(v0, r, dis, GraphMatrix);
		//展示结果
		display(v0, r, dis);
		//结束阶段 
		delete[]dis;
		for (int i = 0; i < r; i++)
			delete[]GraphMatrix[i];
		delete[]GraphMatrix;

		cout << "请再次输入行数和列数:" << endl;
	}
	system("pause");
	return 0;
}
