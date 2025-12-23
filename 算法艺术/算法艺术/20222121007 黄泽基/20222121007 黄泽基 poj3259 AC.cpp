#include<iostream> 
#include<cstring>
#include<queue>

using namespace std;

const int N = 510, M = 5500; //node num; way num 
int f, n, m, w; //counter
int dis[N];
bool vis[N]; //标记存入spfa。 

int h[N], e[M], ne[M], val[M], cnt[N], idx; //cnt记录每个点被访问多少次 



void add(int a, int b, int cost)
{
	e[idx] = b; val[idx] = cost; ne[idx] = h[a]; h[a] = idx++;
}

bool spfa()
{
	memset(dis, 0x3f, sizeof dis); //判负环 
	memset(cnt, 0, sizeof cnt); 
	memset(vis, false, sizeof vis);
	
	dis[1] = 0; //不妨假设从1号节点出发。
		
	queue<int> q; //存节点	
		
	for(int i = 1; i <= n; i ++) 
	{
		q.push(i);
		vis[i] = true;
	}
		
	//spfa：对每个节点遍历n遍，第n遍仍有松弛，则有负环 
	while(!q.empty())
	{
		int t = q.front();
		q.pop();
		
		vis[t] = false; //该节点不在内 
		
		for(int i = h[t]; i != -1; i = ne[i])
		{
			int j = e[i];
			if(dis[j] > dis[t] + val[i])
			{
				dis[j] = dis[t] + val[i];
				cnt[t]++;
				
				if(cnt[t] >= n) return true; //存在负环 
				
				if(!vis[j]) //如果终点没有被访问，到此处松弛 
				{
					q.push(j);
					vis[j] = true;
				}
			}
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin>>f;
	while(f--)
	{
		cin >> n >> m >> w;
		int s, e, t;
		
		idx = 0;
		memset(h, -1, sizeof h); //初始化链表 
		
		
		for(int i = 0; i < m; i++)
		{
			//bidirectional 双向的 
			cin >> s >> e >> t;
			add(s, e, t);
			add(e, s, t);
		}
		
		for(int i = 0; i < w; i++)
		{
			cin >> s >> e >> t;
			add(s, e, -t); //unidirectional 单向的 
		}
			
		bool flag = spfa();
		if(flag) cout << "YES" << endl;
		else cout<< "NO" << endl;
	}

	return 0;
}
