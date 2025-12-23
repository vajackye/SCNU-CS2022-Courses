#include<iostream>

using namespace std;
const int N = 1e5+10;
int n, m;
int parent[N], _size[N];

void init()
{
    for(int i = 1; i <= n; i++)
    {
        parent[i] = i;
        _size[i] = 1;
    }
}

int find(int x)
{
    if(parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void merge(int x, int y)
{
    x = find(x), y = find(y);
    if(x != y)
    {
        parent[x] = parent[y];
        _size[y] += _size[x];
    }
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int cnt = 0;
    while(cin >> n >> m)
    {
        init();
        if(cnt) cout<<endl<<endl;
        cout<<"Case "<< ++cnt <<":";
        for(int i = 0; i < m; i++)
        {
            char op;
            int x, y;  
            cin >> op;
            if(op == 'M')
            {
                cin >> x >> y;
                merge(x, y);
            }
            else
            {
                cin >> x;
                cout<<endl<<_size[find(x)];
            }
        }
    }
    return 0;
}
