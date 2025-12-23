#include<iostream>
using namespace std;

struct seqlist
{
	int data;
	seqlist* node;
	seqlist() :data(),node(NULL) {}
};


void input(seqlist*& head, int size)
{
	int number;
	int maxsize = 0;
	seqlist* ptr = head;
	seqlist* now;
	while (maxsize < size && cin >> number && number != -1)
	{
		now = new seqlist;
		now->data = number;
		ptr->node = now;
		ptr = ptr->node;
		maxsize++;
	}
	ptr->node = head;
}

void output(seqlist*& head)
{
	seqlist* ptr = head->node;
	while (ptr != head)
	{
		cout << ptr->data << " ";
		ptr = ptr->node;
	}
	cout << endl;
}

void clearmin(seqlist*& head)
{
	seqlist* ptr = head;
	seqlist* min = head;
	seqlist* buf = head;
	int min_number = 2147483647;
	while (ptr->node!= head)
	{
		if (ptr->node->data < min_number)
		{
			buf = ptr;
			min_number = ptr->node->data;
			min = ptr->node;
		}
		ptr = ptr->node;
	}
	buf->node = min->node;
	delete min;
}

void clearall(seqlist*& head)
{
	seqlist* ptr = head->node;
	while (head != NULL)
	{
		ptr = ptr->node;
		delete head;
		head = ptr;	
	}
}

int main()
{
	int number;// size
	while (cin >> number && number != -1)
	{
		if (number <= 0)
		{
			cout << "申请空间大小不合法" << endl << "请重新输入：" << endl;
			continue;
		}
		seqlist* head = new seqlist;
		head->data = -1;//-1标志.
		//head->node = head;//循环
		input(head, number);
		output(head);
		clearmin(head);
		output(head);
		clearall(head);
		cout << "再次输入：" << endl;
	}

}
