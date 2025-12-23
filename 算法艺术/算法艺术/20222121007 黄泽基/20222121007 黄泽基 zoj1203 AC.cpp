#include<iostream>
#include<queue>
#include<utility>
#include<cmath>
#include<algorithm>
#include<iomanip> // 引入iomanip头文件

using namespace std;
const int N = 1000;
int n;
double Min; // 使用double类型存储总权值，以便保留小数点后两位

struct s
{
    double x;
    double y;
    int idx;
    
} mz[N];

struct cmp
{
    bool operator()(pair<pair<s,s>, double> &a, pair<pair<s,s>, double> &b)
    {
        return a.second > b.second;
    }
};
   
//朴素并查集
int p[N]; //father

void init()
{
    for(int i = 1; i <= n; i++) 
        p[i] = i;
}

int find(int x)
{
    return x == p[x]? x : find(p[x]);
}

void merge(int x, int y)
{
    x = find(x); y = find(y);
    if(x != y) p[x] = y;
}


void kruskal()
{
    priority_queue<pair<pair<s,s>, double>, vector<pair<pair<s,s>, double>>, cmp> q; 
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            double dis = sqrt(pow(mz[i].x - mz[j].x,2) + pow(mz[i].y - mz[j].y, 2));
            q.push({{mz[i],mz[j]},dis});
            //cout<<q.top().second<<endl;
        }  
    }

    int cnt = 0;
    while(cnt < n - 1)
    {
        s a = q.top().first.first, b = q.top().first.second;
        double dis = q.top().second;
        q.pop();
        if(find(a.idx) == find(b.idx)) continue;
        Min += dis;
        merge(a.idx, b.idx);
        cnt++;
    }
}


int main()
{
    int cnt = 0;
    while(cin>>n && n)
    {
        if(cnt > 0)cout<<endl<<endl;
        Min = 0.00;
        init();
        for(int i = 1; i <= n; i++)
        {
            cin>>mz[i].x>>mz[i].y;
            mz[i].idx = i;
        }
        kruskal();
        cout<<"Case #"<<++cnt<<":"<<endl;
        cout<<"The minimal distance is: "<<fixed<<setprecision(2)<<Min; // 设置精度为两位小数
    }
    return 0;
}

