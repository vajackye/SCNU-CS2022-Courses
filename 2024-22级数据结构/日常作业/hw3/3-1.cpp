#include<bits/stdc++.h> 

using namespace std;
int Maxsize;

class Node
{
public:
	int data;
	Node* next;
	Node() :next(NULL) {}
	Node(int DATA) :data(DATA), next(NULL) {}
};



Node* built(int size)
{
	if (size == 0) return NULL;
	int number;
	cin >> number;
	Node* newNode = new Node(number);
	newNode->next = built(size - 1);
	return newNode;
}

void display(Node* cur)
{
	if (cur == NULL) return;
	cout << cur->data << " ";
	display(cur->next);
	return;
}

//晦涩难懂 
Node* listReversed(Node* cur)
{
	if (cur == NULL || cur->next == NULL) return cur;

	Node* newhead = listReversed(cur->next);
	cur->next->next = cur;
	cur->next = NULL;
	return newhead;

}

int main()
{
	cout << "请输入最大容量" << endl;
	cin >> Maxsize;
	int size;
	while (cin >> size && size != -1)
	{
		if (size <= 0)
		{
			cout << "容量大小不正确" << endl;
			continue;
		}
		if (size > Maxsize)
		{
		 size = Maxsize;
		 cout<<"输入容量超出最大容量，默认输出最大容量容纳的数字"<<endl; 
		} 

		cout << "请输入链表值开始创建链表" << endl;
		int number;
		cin >> number;
		Node* head = new Node(number);
		head->next = built(size - 1);
		display(head);
		cout << endl;
		head = listReversed(head);
		display(head);
		cout<< endl<<endl;
		
	}
	system("pause");
}
