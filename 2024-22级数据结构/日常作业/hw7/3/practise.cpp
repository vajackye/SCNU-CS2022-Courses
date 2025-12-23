#include<iostream>
#include<queue>
#include<stack>
using namespace std;

struct GraphNode
{
	int index; //存序号 
	GraphNode* next = NULL;
};

struct GraphTable
{
	int w = 0;//权重
	bool vis = false;//入队置true 
	GraphNode* adj = NULL;
};

//构造
void getNebNode(GraphTable table[], int n)
{
	int ind;
	for (int i = 0; i < n; i++)
		while (cin >> ind && ind != -1)
		{
			GraphNode* tmp = new GraphNode;
			tmp->index = ind;
			tmp->next = table[i].adj;
			table[i].adj = tmp;
		}
}

//计算每个结点入度
void countInd(GraphTable table[], int n)
{
	for (int i = 0; i < n; i++)
	{
		GraphNode* tmp = table[i].adj;
		while (tmp != NULL)
		{
			table[tmp->index].w++;
			tmp = tmp->next;
		}
	}
}
//topo排序
void topo(GraphTable table[], int n)
{
	countInd(table, n);
	queue<int> q; //索引表,入度为0则入度
	int count = 0;
	for (int i = 0; i < n; i++)
		if (table[i].w == 0)
		{
			q.push(i);//先将入度为0的入度
			count++;
		}
	//topo
	while (!q.empty())
	{
		//展示
		int index = q.front();
		q.pop();//取出第一个元素
		cout << index << " ";
		GraphNode* tmp = table[index].adj;
		table[index].vis = true;
		
		while (tmp != NULL)
		{
			table[tmp->index].w--;
			if (table[tmp->index].w == 0&& table[tmp->index].vis==false)
			{
				q.push(tmp->index);
				count++;
			}
			tmp = tmp->next;
		}
	}

	if (count != n)cout << "存在回路" << endl;
	else cout << endl;

}

//删除
void delELem(GraphTable table[], int n)
{
	
	for (int i = 0; i < n; i++)
	{
		GraphNode* tmp = table[i].adj;
		while (table[i].adj != NULL)
		{
			tmp = tmp->next;
			delete table[i].adj;
			table[i].adj = tmp;
		}
	}
	delete[]table;
}

void display(GraphTable table[], int n)
{
	for (int i = 0; i < n; i++)
	{
		GraphNode* tmp = table[i].adj;
		cout << "数组表" << i << "下标" << " ";
		while (tmp != NULL)
		{
			cout << tmp->index << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}
}

int main()
{
	int n;
	cout<<"请输入节点个数"<<endl; 
	while (cin >> n && n != -1)
	{
		if(n==0)
		{
			cout<<"0!"<<endl;
			cout << "请再次输入每个结点的邻接结点序号，默认顺序从0开始，-1终止" << endl;
			continue; 
		}
		//初始化
		GraphTable *table = new GraphTable[n];
		cout << "请输入每个结点的邻接结点序号,默认顺序从0开始，-1终止" << endl;
		getNebNode(table, n);
		display(table, n);
		topo(table, n);
		//析构
		delELem(table, n);
		cout << "请再次输入节点个数，-1终止" << endl;
	}
	system("pause");
	return 0;
}
