#include<iostream>
using namespace std;
void adjust(int a[], int start, int len)
{
	int son = start * 2 + 1;
	int fa = start;
	int tmp = a[fa];

	while (son <= len)
	{
		if (son<len && a[son] < a[son + 1])
			son++;
		if (tmp < a[son])
		{
			a[fa] = a[son];
			fa = son;
			son = fa * 2 + 1;
		}
		else break;
	}

	a[fa] = tmp;
}

void heapSort(int a[], int size)
{
	//先调整 
	for (int i = size/2-1; i >=0; i--)
		adjust(a, i, size-1);

	//堆排序
	for (int i = size - 1; i >= 1; i--)
	{
		swap(a[0], a[i]);//调整
		adjust(a, 0, i-1);//继续调整 
	}
}
//从0开始存储。 
int main()
{
	int num;
	cout << "输入元素个数：";
	while (cin >> num && num != -1)
	{
		int* a = new int[num];
		cout << "依次输入元素值:" << endl;

		for (int i = 0; i < num; i++)
			cin >> a[i];
		cout << "排序前：" << endl;
		for (int i = 0; i < num; i++)
			cout << a[i] << " ";
		cout << endl;
		cout << "排序后：" << endl;
		heapSort(a, num);
		for (int i = 0; i < num; i++)
			cout << a[i] << " ";
		delete[]a;
		cout << "再次输入元素个数：";
	}
	system("pause");
	return 0;
}
