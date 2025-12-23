//#include<iostream>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//int n, a[25], dir[30][30]; //dir存边关系,a存储输入字母相对大小（a[i] = 字母 - 'a'）
//int topo[25], vis[30], indegree[30];  //top排序，访问过，入度，数量看题大小
//
//void dfs(int sta, int cnt) //cnt统计个数，如果达到个数，输出拓扑排序一种, sta为入度为0的，优先级max
//{
//	int i;
//	topo[cnt] = sta; //顺序拓扑，记录顺序
//	if (cnt == n - 1) //取完所有结点，输出一个结果返回
//	{
//		for (int i = 0; i < n; i++) cout << char(topo[i] + 'a'); //用整数9字母差）代替字母存储，加回来
//		cout << endl;
//		return;
//	}
//
//	vis[sta] = 1; //cnt < n-1,继续；入度点已拜访过
//	for (i = 0; i < n; i++)
//	{
//		if (!vis[a[i]] && dir[sta][a[i]])  //vis[a[i]]即该点未拜访过，且与sta结点有边
//		{
//			indegree[a[i]]--;//与sta有关边去掉，则入度--
//		}
//	}
//	for (i = 0; i < n; i++) //继续dfs
//	{
//		if (!indegree[a[i]] && !vis[a[i]]) //入度为0且，未访问过该字母
//			dfs(a[i], cnt + 1);//cnt++，记录数量.
//	}
//	//回溯，取消拜访。寻找下一组拓扑
//	for (i = 0; i < n; i++)
//		if (!vis[a[i]] && dir[sta][a[i]])
//			indegree[a[i]]++;
//	vis[sta] = 0;
//
//}
//
//int main()
//{
//	string s;
//	int len;
//	while (getline(cin, s))
//	{
//		memset(dir, 0, sizeof(dir));
//		memset(vis, 0, sizeof(vis));
//		memset(indegree, 0, sizeof(indegree));
//		len = s.size();
//		n = 0; //记录字母长度，用于给a[i]存放迭代
//		for (int i = 0; i < len; i++)  //存字母相对大小于a[i]中
//		{
//			if (s[i] <= 'z' && s[i] >= 'a')        //特判读入的空格符号
//				a[n++] = s[i] - 'a';
//		}
//		sort(a, a + n);  //对字母排序，这样就能按字典序输出了。//不影响入度出度，只是改变同入度大小的结点的先后顺序，输出字典序
//		getline(cin, s); //输入拓扑关系
//		len = s.size();
//		int first = 1;//first=1表示当前字母是起点
//		int start, end;//出度点，入度点
//		for (int i = 0; i < len; i++)//处理先后关系
//		{
//
//			if (first && s[i] <= 'z' && s[i] >= 'a')//起点
//			{
//				first = 0;
//				start = s[i] - 'a';  //字母转换成数字。
//				continue;
//			}
//			if (!first && s[i] <= 'z' && s[i] >= 'a')//终点
//			{
//				first = 1;
//				end = s[i] - 'a';
//				dir[start][end] = 1; //记录先后关系
//				indegree[end]++;  //终点入度++
//				continue;
//			}
//		}
//		for (int i = 0; i < n; i++)
//			if (!indegree[a[i]])  //始边，入度点为0的优先级最高，开始dfs
//				dfs(a[i], 0);  //a[i]传入相对大小，0表示cnt，当统计到cnt-1结束，输出一组拓扑结果
//		cout << endl;
//	}
//	return 0;
//}
//#include<bits/stdc++.h>
//using namespace std;
//const int N = 55;
//int degree[N];  //记录度
//int G[N][N];  //记录边关系。将颜色当成两个点，珠子当成边。
//void euler(int u)  //从u开始dfs
//{
//    for (int v = 1; v <= 50; v++)  //v是u的邻居
//    {
//        if (G[u][v])
//        {
//            //相关边--
//            G[u][v]--;
//            G[v][u]--;
//            euler(v); //dfs邻居。不存在重边情况下，再小循环内死循环。因为标号同。比如从6开始，下一个v是1，那下次迭代，从1开始，自身，再到2，（1，2），下一个就是2了，在下次（2，1）已经--，而且再main里已经去掉奇点了。
//            cout << v << " " << u << endl; //回溯时打印，逆序。不影响，起点终点一样的。
//        }
//    }
//}
//
//int main()
//{
//    int t, cnt = 0;
//    cin >> t;
//    while (t--)
//    {
//        cnt++;//用于输出题目换行
//        if (cnt != 1) cout << endl;
//        cout << "Case #" << cnt << endl;
//        memset(degree, 0, sizeof(degree));
//        memset(G, 0, sizeof(G));
//        int n; 
//        cin >> n;
//        int color;  //记录其中一个颜色，从任意一个颜色开始遍历即可。
//        for (int i = 0; i < n; i++)   //n条边
//        {
//            int u, v;
//            cin >> u >> v;
//            color = u; //随机记录一种颜色。待会随机用一个点开始遍历。
//            degree[u]++; //度数++（无向图）
//            degree[v]++; //度数++（无向图）
//            G[u][v]++;  //存图，双向的（无向图）
//            G[v][u]++;
//        }
//        int ok = 1;
//        for (int i = 1; i <= 50; i++)
//        {
//            if (degree[i] % 2) { //存在奇点，（重边，除非全部重一遍（再次回路），否则必有奇点，（只出不入，只入不出）。
//                cout << "some beads may be lost" << endl;
//                ok = 0; //不ok了，不成路
//                break;
//            }
//        }
//        if (ok) euler(color); //开始随便找一个颜色遍历。
//    }
//    return 0;
//}
#include<bits/stdc++.h> 

using namespace std;


class mylist
{
public:
	int value;
	mylist* node;
	mylist() :node(NULL) {};
};

void builtlist(int arr[], int number, mylist* head)
{
	mylist* ptr = head->node;
	mylist* cur = head;
	int flag = 0; // 0表示为0
	for (int i = 0; i < number * 2 - 1; i++)
	{
		flag = arr[i] == 0 ? 0 : 1;
		if (flag != 0 && arr[i + 1] == 0 && arr[i + 2] == 0)
		{
			ptr = new mylist();
			ptr->value = arr[i];
			cur->node = ptr;
			cur = cur->node;
			ptr = ptr->node;
		}
	}
}


void show(mylist* head)
{
	mylist* cur = head->node;
	while (cur != NULL)
	{
		cout << cur->value << " ";
		cur = cur->node;
	}
	cout << endl;
}

void delist(mylist* head)
{
	mylist* cur = head;
	while (head != NULL)
	{
		//顺序引发异常
		cur = cur->node;
		delete head;
		head = cur;

	}
}
int main()
{
	int n;
	cout << "输入要测试的二叉树组数：" << endl;
	cin >> n;
	while (n--)
	{
		int arr[256];
		int number;
		cout << "该组二叉树结点数量：" << endl;
		cin >> number;
		if (number <= 0)
		{
			cout << "空树，空链表" << endl;
			continue;
		}
		cout << "输入二叉树的前序遍历" << endl;
		for (int i = 0; i < 2 * number + 1; i++)
		{
			cin >> arr[i];
		}
		mylist* head = new mylist();
		builtlist(arr, number, head);
		show(head);
		delist(head);
	}
	system("pause");
	return 0;
}



