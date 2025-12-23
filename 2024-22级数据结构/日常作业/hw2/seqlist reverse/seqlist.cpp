/*
该算法指针有点问题，无法使用如 ptr != 0操作，仍旧输出，且自动默认为data = 0
需要通过data != 0 解决
已修正，通过构造函数link(NULL)
其中，在input中，会多创造一个space
解决：添加一个indexout检测溢出。但在析构中可以全部释放空间
法二：在input最后在delete cur，清除多余
*/


#include<iostream>
using namespace std;


template<class T>
class LinkNode
{
public:
	T data;

	LinkNode* link;
	LinkNode();
};

template<class T>
LinkNode<T>::LinkNode() :link(NULL) {
}


template<class T>
class List :protected LinkNode<T>
{
private:
	LinkNode<T>* head;
	LinkNode<T>* new_head;
	int maxsize;
	int indexout;
public:
	List(int Maxsize);
	void input();
	void reversed();
	void output();
	~List();
};

template<class T>
List<T>::List(int Maxsize)
{
	
	indexout = 0;
	head = new LinkNode<T>();
	head->data = 0; // 虚拟头节点
	new_head = head;
	maxsize = Maxsize;
	head->link = NULL;
	input();
	reversed();
	
	
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
		indexout++;
		cur->data = num;
		ptr = cur;
		cur = cur->link;
		cur = new LinkNode<T>();
		ptr->link = cur;
	}
	output();
	
	return;
}

template<class T>
void List<T>::reversed()
{
	LinkNode<T>* pre = head->link;
	LinkNode<T>* rev = pre;
	while (pre != NULL)
	{
		pre = pre->link;
		rev->link = new_head;
		new_head = rev;
		rev = pre;
	}
	head->link = NULL;
	//delete head;//delete不了？没构造吗？应该有nullptr'
	//if (head->link == NULL) cout << "删除";
	head = new_head;
	cout << "逆置后元素：" << endl;
	output();
	return;
}

template<class T>
void List<T>::output()
{
	LinkNode<T>* ptr = head->link;
	int cnt = 0;//多开辟了一个空间，需要计数，防止多输出一个
	while (ptr != NULL && cnt < indexout)//nullptr
	{
		cnt++;
		cout << ptr->data << " ";
		ptr = ptr->link;
	}
	cout << endl;
	return;

}

template<class T>
List<T>::~List()
{
	LinkNode<T>* ptr = new_head;
	LinkNode<T>* store = new_head;
	while (ptr != NULL)
	{
		store = store->link;
		delete ptr;
		//cout << "shanchu";
		ptr = store;
		
	}
}

int main()
{
	int size;
	while (cin >> size && size != -1)
	{
		if (size < 1)
		{
			cout << "数据长度错误！";
			cout << "再次输入：" << endl;
		}
		List<int> test(size);
		
		cout << "再次输入：" << endl;
	}
	
	return 0;
}
