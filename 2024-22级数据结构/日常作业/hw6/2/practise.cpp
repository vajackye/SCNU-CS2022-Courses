#include<iostream>
#include<queue>

using namespace std;
struct edge
{
	int dest = 0;
	edge* next = NULL;
};

struct vertex
{
	bool visited = false;
	edge* adj = NULL;
	void clear();
};
//析构边
void vertex::clear()
{
	edge* tmp = this->adj;
	while (this->adj != NULL)
	{
		tmp = tmp->next;//顺序不能乱
		delete this->adj;
		this->adj = tmp;
		
	}
}
//析构结点
void clearVer(vertex table[])
{
	delete[]table;
}

//重置vertex 
void restart(int n, vertex table[])
{
	for (int i = 0; i < n; i++)
		table[i].visited = false;
}

//加边,头插法
void add(int a, int b, vertex table[])
{
	edge* p = new edge;
	p->dest = b;
	p->next = table[a].adj;
	table[a].adj = p; //头插法
}

void Init(int v, vertex table[])
{
	int nod;
	cout << "输入邻接表结点:" << endl;
	while (cin >> nod && nod != -1)
	{
		add(v, nod, table);
	}
}

//深度优先遍历
void dfs(int v, vertex table[])
{
	table[v].visited = true;
	edge* tmp = table[v].adj;
	while (tmp != NULL)
	{
		if (!table[tmp->dest].visited)
		{
			cout << v << "->" << tmp->dest << " ";
			dfs(tmp->dest, table);
			tmp = tmp->next;
		}
		else tmp = tmp->next;
	}

	return;
}

//广度优先遍历
void bfs(int v, vertex table[])
{
	queue<int>q;
	q.push(v);
	table[v].visited = true;
	while (!q.empty())
	{
		int tmp = q.front();
		edge* node = table[tmp].adj;
		q.pop();
		while (node != NULL)
		{
			if (!table[node->dest].visited)
			{
				cout << tmp << "->" <<node->dest<< " ";
				q.push(node->dest);
				table[node->dest].visited = true;
				node = node->next;
			}
			else node = node->next;
		}
	}

}
int main()
{
	int n;
	cout << "请输入节点个数：" << endl;
	while (cin >> n && n != -1)
	{

		vertex* table;
		table = new vertex[n];
		cout << "初始化边：" << endl;
		for (int i = 0; i < n; i++)
		{
			Init(i, table);

		}
		cout << "请输入开始深度遍历的结点" << endl;
		int dot;
		cin >> dot;
		dfs(dot, table);

		//重置
		restart(n, table);
		cout<<"请输入开始广度遍历的结点" << endl;
		cin >> dot;
		bfs(dot, table);
		for (int i = 0; i < n; i++)
		{
			table[i].clear();
		}
		clearVer(table);
		cout << "请再次输入节点个数：" << endl;
	}
	system("pause");
}
