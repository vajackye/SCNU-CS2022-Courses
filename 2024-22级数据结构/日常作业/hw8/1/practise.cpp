
#include<iostream>
using namespace std;
int Qpass(int a[], int l, int r)
{
	int low, high;
	low = l; high = r;
	int store = a[low];//记录基准值
	while (low < high)
	{
		while (low < high && store <= a[high])high--;//从右往左扫描
		if (low < high)  a[low++] = a[high];
		while (low < high && store >= a[low])low++;//从左往右扫描 
		if (low < high) a[high--] = a[low];
	}
	a[low] = store;
	return low;//返回中点mid 
}

void qsort(int a[], int l, int r)
{
	int mid; //基准值
	if (l < r)
	{
		mid = Qpass(a, l, r);
		qsort(a, l, mid - 1);//左递归 
		qsort(a, mid + 1, r);//右递归 
	}
}

int main()
{
	int num;
	cout << "请输入要排序的元素的个数：" << endl;
	while (cin >> num && num != -1)
	{
		int* a = new int[num];
		cout << "请依次待排序元素：" << endl;
		for (int i = 0; i < num; i++)
			cin >> a[i];

		cout << "待排序前的元素序列:" << endl;
		for (int j = 0; j < num; j++)
			cout << a[j] << " ";
		cout << endl;

		qsort(a, 0, num - 1);
		cout << "排序后的元素序列：" << endl;
		for (int k = 0; k < num; k++)
			cout << a[k] << " ";
		cout << endl;
		delete[]a;

		cout << "请再次输入要排序的元素个数：" << endl;
	}
	system("pause");
}
