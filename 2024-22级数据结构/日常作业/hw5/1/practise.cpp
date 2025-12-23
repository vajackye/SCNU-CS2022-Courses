#include<iostream>
#include<vector>
using namespace std;

class BSTNode
{
public:
	int data;
	BSTNode* l, * r;
	BSTNode() :l(NULL), r(NULL) {}
	BSTNode(int da) :data(da), l(NULL), r(NULL) {}
};

BSTNode* BSTCreat()
{
	int x;
	cin >> x;
	if (x == 0) return NULL; //¿Õ½áµã
	BSTNode* root = new BSTNode(x);
	root->l = BSTCreat();
	root->r= BSTCreat();
	return root;
}

void Inorder(BSTNode* root, vector<int>& stor)
{
	if(root == NULL) return;
	Inorder(root->l, stor);
	stor.push_back(root->data);
	Inorder(root->r, stor);
	return ;
}

void search(vector<int>& stor)
{
	for(int i = 0; i < stor.size()-1; i++)
		if(stor[i] >= stor[i+1])
		{
			cout<<"NO"<<endl;
			return;
		}
	cout<<"YES"<<endl;
	return; 
}

int main()
{

	int n;
	while (cin >> n && n != -1)
	{

		BSTNode* root = BSTCreat();
		vector<int> stor;
		Inorder(root, stor);
		search(stor);
	}
	return 0;
}
