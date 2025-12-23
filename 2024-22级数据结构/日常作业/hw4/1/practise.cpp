#include<bits/stdc++.h> 

using namespace std;

class tree
{
public:
	int value;
	tree* left;
	tree* right;
	tree() :left(NULL), right(NULL) {}
};

tree* builtTree()
{
	int num;
	tree* cur;
	cin >> num;
	if (num == -1)
		return NULL;
	else
	{
		cur = new tree();
		cur->value = num;
		cur->left = builtTree();
		cur->right = builtTree();
		return cur;
	}
}



void midOrder(tree* p)
{
	stack<tree*> st;
	tree* ptr = p;
	while(!st.empty()||ptr!=NULL) 
	{
		while(ptr!=NULL)
		{
			st.push(ptr);
			ptr = ptr->left;
		}
		if(!st.empty())
		{
			ptr = st.top();
			st.pop();
			cout<<ptr->value<<" ";
			ptr=ptr->right;
		}
	}
}


//后序遍历销毁二叉树。
void detele_ptr(tree* p)
{
	if (p == NULL) return;
	detele_ptr(p->left);
	detele_ptr(p->right);
	delete p;
}

int main()
{
	int n;
	cout << "输入测试次数：";
	cin >> n;
	cout << endl;
	while (n--)
	{
		tree* p = builtTree();
		if (p == NULL)
		{
			cout << "空树" << endl;
			continue;
		}
		midOrder(p);
		cout<<endl;
	}
	system("pause"); 
	return 0;
}



