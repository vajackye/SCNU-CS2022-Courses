#include<bits/stdc++.h> 

using namespace std;
const int N = 1010;
string ss;
int store[N][N];

//if str[st] == str[ed] -->continue?
//if str[st] != str[ed] min(cnt[st] , cnt[ed])


//Çø¼ädp 
int cost(int st, int ed)
{
	if(st >= ed) return 0; // overflow
	
	if(store[st][ed] != -1) return store[st][ed];
	
	if(ss[st] == ss[ed]) return store[st][ed] = cost(st + 1, ed - 1);
	
	//not equal
	int l = cost(st + 1, ed);
	int r = cost(st, ed - 1);
	
	return store[st][ed] = min(l, r) + 1; //return min insert 
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	
	getline(cin,ss);
	cout<<ss<<endl;
	
	if(ss.size()<=1) 
	{
		cout<<0<<endl;
		return 0;
	}
	//cout<<ss.size()<<endl;
	memset(store, -1, sizeof store);
	int st = 0, ed = ss.size()-1;
	cost(st, ed);
	cout<<store[st][ed]<<endl;
	return 0;
}
