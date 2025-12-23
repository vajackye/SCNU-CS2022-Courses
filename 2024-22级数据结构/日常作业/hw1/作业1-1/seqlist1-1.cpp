/*
* 用数组模拟 插入排序 保持元素的有序性
* 即插入在第n个位置时，从后往前至n循环后插，后插确保元素覆盖正确
* 算法鲁棒性检测：头插，尾插，空元素，满元素，一般情况
* 复杂度：O(n)
*/
#include<stdlib.h>
#include<iostream>
using namespace std;

template<class T>
class seqlist
{
private:
	T* data;
	int last;
	int maxsize;

public:
	seqlist(int size);
	void getdata();
	void printans();
	void insert_(T number);
	~seqlist();
};

//初始化，包括申请空间，下标，最大空间 
template<class T>
seqlist<T>::seqlist(int size)
{
	maxsize = size;
	last = -1;
	data = new T[maxsize];
	if (data == 0)
	{
		cout << "申请空间失败！";
		return;
	}
	getdata();
}

//获取数据 
template<class T>
void seqlist<T>::getdata()
{
	T num;
	for (int i = 0; i < maxsize; i++)
	{
		if (last == maxsize - 1)
		{
			cout << "插入元素已满" << endl;
			printans();
			return;
		}
		cin >> num;
		if (num == -1) break;
		data[i] = num;
		last++;
	}
	printans();
	int number;
	cin >> number;
	insert_(number);
}

template<class T>
void seqlist<T>::printans()
{
	for (int i = 0; i <= last; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

template<class T>
void seqlist<T>::insert_(T number)
{
	//if(maxsize <= 0) return; //不用添加，因为在构造exit中退出 
	int index = 0;
	//搜索 
	for (index; index <= last; index++)
	{
		if (data[index] > number)
		{
			break;
		}
		//cout << index;
	}

	if (index == maxsize) exit(1); //错误点，写成了maxsize-1，应该是maxsize，因为最后一次index==4时，与最后一项比完还要+1
	//插入 
	for (int i = last + 1; i > index; i--)
	{
		if (last == maxsize - 1)
		{
			cout << "超出大小限制，默认清除最后一项";
			last--;
			continue;
		}
		data[i] = data[i - 1];
	}
	data[index] = number;
	last++;
	printans();
	return;
}

template<class T>
seqlist<T>::~seqlist()
{
	if (data != 0)
	{
		delete[] data;
	}
}

int main()
{
	int size;
	cout << "输入size大小：";
	cout << endl;
	while (cin >> size && size != -1)
	{
		if (size <= 0)
		{
			cout << "大小不对！再次输入" << endl;
			continue;
		}
		seqlist<int> test(size);
		cout << "再次输入：" << endl;
	}

	return 0;
}
