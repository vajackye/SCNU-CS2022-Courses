#include<bits/stdc++.h> 

using namespace std;
vector<int> lst;
vector<int> mid;

class treeNode
{
public:
	int value;
	treeNode* left;
	treeNode* right;
	treeNode() :left(NULL), right(NULL) {}
};

int midFind(int root);
treeNode* builtTree(int l, int r, int ml, int mr)
{
	if (l > r) return NULL; // 寻找结束

	//后序找出根节点
	int root = lst[r];
	treeNode* cur = new treeNode();
	cur->value = root;

	//找到中序中，根节点的索引，划分左右子树 
	int index = midFind(root);
	int numleft = index - ml;
	cur->left = builtTree(l,l+numleft-1, ml, index-1);
	cur->right = builtTree(l+numleft, r-1, index+1, mr);

	return cur;
}

int midFind(int root)
{
	for (int i = 0; i < mid.size(); i++)
		if (root == mid[i]) return i;
}


void show(treeNode* father)
{
	if (father == NULL) return;
	cout << father->value << " ";
	show(father->left);
	show(father->right);
}


void delist(treeNode* father)
{
	if (father == NULL) return;
	delist(father->left);
	delist(father->right);
	delete father;
}

void getOrder(int n)
{
	while (n--)
	{
		cout << "请输入后序遍历,以-1结束" << endl;
		int num;
		while (cin >> num && num != -1)
		{
			lst.push_back(num);
		}
		cout << "请输入中序遍历,以-1结束" << endl;
		while (cin >> num && num != -1)
		{
			mid.push_back(num);
		}
		
		treeNode* father = builtTree(0,lst.size() - 1,0,mid.size());
		show(father);
		lst.clear();
		mid.clear();
		delist(father);
	}
}




int main()
{
	int n;
	cout << "输入测试二叉树的组数:" << endl;
	cin >> n;
	getOrder(n);
	system("pause");
	return 0;
}



