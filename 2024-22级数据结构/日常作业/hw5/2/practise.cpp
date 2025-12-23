#include<bits/stdc++.h>
using namespace std;
vector<int> ans;
class BST
{
public:
	bool delFlag; 
	int data;
	BST* left;
	BST* right;	
	BST():left(NULL), right(NULL){delFlag = true;}

};

void del(BST* root)
{
	if(root== NULL) return;
	del(root->left);
	del(root->right);
	delete root;
}

BST* root;
//插入 
int insert(int x)
{
	BST *a, *fa, *p;
	a = root, fa=0;
	while(a!=NULL)
	{
		if(x==a->data) return -1; //已存在该元素
		else if(x < a->data)
		{
			fa = a;
			a = a->left;
		 } 
		 else
		 {
		 	fa = a;
		 	a = a->right;	
		 }
	}
	p = new BST;
	p->data = x;
	if(fa == NULL) root = p;
	else if(x > fa->data) fa->right = p;
	else fa->left = p;
	return 1; //succeed！ 
}


void Creat()
{
	int n;
	while(cin>>n&&n!=-1)
	{
		insert(n);
	}
	return;
}

int search(int x)
{
	BST* p = root;
	while(p!=NULL)
	{
		if(p->data == x) return 1; //找到
		else if(p->data > x) p = p->left;
		else p = p->right; 
	}
	return -1;//没找到 
}

int delNode(int x)
{
	BST* p = root;
	while(p!=NULL)
	{
		if(p->data == x)
		{
			p->delFlag = false;
			return 1; //删除成功 
		}
		else if(p->data > x) p = p->left;
		else p = p->right; 
	}
	return -1; //没找到删除对象 
}

//输出 
void disPlay(BST* node)
{
	if(node == NULL)
		return;
	disPlay(node->left);
	if(node->delFlag) cout<<node->data<<" ";
	disPlay(node->right);
	return;
}

int main()
{
	int x;
	Creat();
	cin>>x;
	if(search(x) == 1)
		cout<<"找到！";
	else cout<<"未找到！";
	cin>>x;
	if(search(x) == 1)
		cout<<"找到！";
	else cout<<"未找到！";
	cin>>x;
	insert(x);
	disPlay(root);
	cin>>x;
	delNode(x);
	disPlay(root);
	system("pause"); 
 } 
