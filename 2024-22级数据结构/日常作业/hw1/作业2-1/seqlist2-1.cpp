
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
	void clearmin();
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
		exit(1);
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
			break;
		}
		cin >> num;
		if (num == -1) break;
		data[i] = num;
		last++;
	}
	printans();
	clearmin();
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
void seqlist<T>::clearmin()
{

	int book = 0;
	int min = 0x7fffffff;
	//搜索 
	for (int index = 0; index <= last; index++)
	{
		if (data[index] < min)
		{
			min = data[index];
			book = index;
		}
		//cout << index;
	}
	//index = maxsize
	for (int i = book; i < last; i++)
	{
		data[i] = data[i + 1];
	}
	last--;
	cout << "删除后：" << endl;
	printans();
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
	
	while (cin >> size && size != -1)
	{
		if (size < 1)
		{
			cout << "申请空间大小不正确！" << endl;
			cout << "再次输入：" << endl;
			continue;
		}
		seqlist<int> test(size);
		
		//test.printans();
		//cin >> number;
		
		
		cout << "再次输入：" << endl;
	}

	system("pause");
	return 0;
}
