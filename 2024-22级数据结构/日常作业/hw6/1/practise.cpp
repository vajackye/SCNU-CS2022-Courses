#include<iostream>
#include<queue>
using namespace std;

class GraphMatrix
{
public:
	int** Edge;//二维数组。用此来访问顶点标记（[i][i]) 
	int* vertex; //顶点集合
	int row;
	int col;
	GraphMatrix() :row(0), col(0) {}
	GraphMatrix(int r, int c) :row(r), col(c)
	{
		Edge = new int* [row];
		for (int i = 0; i < r; i++)
			Edge[i] = new int[col];
		vertex = new int[row];
	}
	~GraphMatrix()
	{
		delete[]vertex;
		for (int i = 0; i < row; i++)
			delete []Edge[i];
		delete[]Edge;
	}
	//输入 
	void getVerAndEdge();
	//输出
	void prinVerAndEdge();
	//重置
	void restart()
	{
		for (int i = 0; i < row; i++)
			this->Edge[i][i] = 0;//重置访问
	}
};

void GraphMatrix::getVerAndEdge()
{
	cout << "请输入每行数据" << endl;
	for (int i = 0; i < row; i++)
	{
		vertex[i] = 1;
		for (int j = 0; j < col; j++)
			cin >> Edge[i][j];
	}

}

void GraphMatrix::prinVerAndEdge()
{
	cout << "展示输入结果:" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << Edge[i][j] << " ";
		cout << endl;
	}
}

//深度
void dfs(int start, GraphMatrix& mat, int lenth, bool& flag)
{
	if (lenth == mat.col) return; //全部节点遍历完毕，提前结束
	for (int i = 0; i < mat.col; i++)
		if (mat.Edge[start][i]== 1 && !mat.Edge[i][i])//未被访问,且可达
		{
			cout << start << "->" << i << " ";
			mat.Edge[i][i] = 1;
			flag = true;
			dfs(i, mat, lenth+1, flag);
		}
}

//广度
void bfs(int start, GraphMatrix& mat, bool& flag)
{
	queue<int> q;
	q.push(start);
	mat.Edge[start][start] = 1;
	while (!q.empty())
	{
		int sta = q.front();
		q.pop();
		for (int i = 0; i < mat.col; i++)
			if (mat.Edge[sta][i] == 1 && !mat.Edge[i][i])
			{
				flag = true;
				mat.Edge[i][i] = 1;
				cout<< sta << "->" << i << " ";
				q.push(i);
			}	
	}
}


int main()
{
	int r, c;
	cout << "请依次输入行数和列数，-1，-1表退出程序" << endl;
	while (cin >> r >> c && r != -1 && c != -1)
	{
		GraphMatrix tmp(r, c);
		tmp.getVerAndEdge();
		tmp.prinVerAndEdge();
		cout << "请输入深度出发节点:" << endl;
		int dot;
		cin >> dot;
		tmp.Edge[dot][dot] = 1;
		bool flag = false;
		cout << "深度输出为：" << endl;
		dfs(dot, tmp,1, flag);
		if (flag == false) cout<<"无可达邻接点";
		cout << endl;

		flag = false;
		tmp.restart();
		cout << "请输入广度出发节点:" << endl;
		cin >> dot;
		cout << "广度输出为：" << endl;
		bfs(dot,tmp,flag);
		if (flag == false) cout << "无可达邻接点" << endl;


		cout << "请再次输入行数和列数" << endl;
	}
	system("pause");
	return 0;
}
