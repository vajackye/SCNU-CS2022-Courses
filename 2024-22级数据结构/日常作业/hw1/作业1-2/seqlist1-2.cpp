#include<iostream>
using namespace std;

template<class T>
class LinkNode
{
public:
	T data;

	LinkNode* link;
};


template<class T>
class List :protected LinkNode<T>
{
private:
	LinkNode<T>* head;
	int maxsize;
	int indexrember;
public:
	List(int Maxsize);
	void input();
	void insert_(T number);
	void output();
	~List();
};

template<class T>
List<T>::List(int Maxsize)
{
	head = new LinkNode<T>();
	head->data = 0; // 虚拟头节点
	if (Maxsize < 1)
	{
		cout << "数据长度错误！";
		exit(1);
	}
	maxsize = Maxsize;
	head->link = 0;
	cout << "输入数据:";
	input();
}

template<class T>
void List<T>::input()
{
	LinkNode<T>* cur = new LinkNode<T>();
	head->link = cur;
	LinkNode<T>* ptr;
	for (int i = 0; i < maxsize; i++)
	{
		int num;
		cin >> num;
		if (num == -1) break;
		cur->data = num;
		ptr = cur;
		cur = cur->link;
		cur = new LinkNode<T>();//无法使用NULL问题在这里，多开辟了一个space 
		ptr->link = cur;
		indexrember++;
	}
	output();
	int number;
	cout << "输入要插入数据" << endl;
	cin >> number;
	insert_(number);
	return;
}

template<class T>
void List<T>::insert_(T number)
{
	if (indexrember == maxsize)
	{
		cout << "存储已满" << endl;
		return;
	}
	LinkNode<T>* cur = head->link;
	LinkNode<T>* ptr = cur;
	int first_ins_spectial = 0;
	for (int i = 0; i < maxsize; i++)
	{
		if (cur->data == 0) break;//nullptr
		if (cur->data > number)
		{
			break;
		}
		first_ins_spectial++;
		ptr = cur;
		cur = cur->link;
	}
	//针对头插法死循环
	if (first_ins_spectial == 0)
	{
		LinkNode<T>* now = new LinkNode<T>();
		ptr = head;
		now->data = number;
		ptr->link = now;
		now->link = cur;
		output();
		return;
	}
	LinkNode<T>* now = new LinkNode<T>();
	now->data = number;
	ptr->link = now;
	now->link = cur;//头插法有问题
	output();
	return;
}

template<class T>
void List<T>::output()
{
	LinkNode<T>* ptr = head->link;
	while (ptr->data != 0)//nullptr
	{
		cout << ptr->data << " ";
		ptr = ptr->link;
	}
	cout << endl;
	return;

}

template<class T>
List<T>::~List()
{
	LinkNode<T>* ptr = head;
	LinkNode<T>* store = head->link;
	while (store->data != 0)
	{
		delete ptr;
		ptr = store;
		store = store->link;
	}
}

int main()
{
	int size;
	while (cin >> size && size != -1)
	{
		if (size == 0)
		{
			cout << "无" << endl;
			cout << "再次输入：" << endl;
			continue;
		}
		List<int> test(size);
		cout << "再次输入：";
	}
	system("pause");
	return 0;
}
