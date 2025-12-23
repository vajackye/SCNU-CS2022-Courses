//floyd做法，floyd核心：节点编单独点号
#include<bits/stdc++.h>

using namespace std;
int vis[65][65];
int maze[65][65]; //给每个点编号，每个点i->j即第i个点到第j个点 

void number_code() //主要在于建图：floyd每个点都得有一个编号，不能二维编号。[i][j]表示i节点->j节点 
{
	for (int i = 1; i <= 64; i++)
	{
        maze[i][i] = 0;
		for (int j = 1; j <= 64; j++)
		{
			int x = abs((i-1) / 8 - (j-1) / 8), y = abs((i-1) % 8 - (j-1) % 8); //y<64,or 逆反
			if (x == 1 && y == 2 || x == 2 && y == 1)
			{
				maze[i][j] = maze[j][i] = 1;
			}
		}
	}
}

void floyd()
{
	for (int k = 1; k <= 64; k++)
		for (int i = 1; i <= 64; i++)
			for (int j = 1; j <= 64; j++)
			{
				if (maze[i][j] > maze[i][k] + maze[k][j])
					maze[i][j] = maze[i][k] + maze[k][j];
			}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	string a, b;
	vector<pair<int, int>> place; //需要处理的所有输入。 
	vector<pair<string, string>> str; 
    
    memset(maze, 0x3f, sizeof maze);
	number_code();
	while (cin >> a >> b)
	{
		int i_a = (a[0] - 'a') * 8, j_a = (a[1] - '0'); //从1开始 
		int i_b = (b[0] - 'a') * 8, j_b = (b[1] - '0');
		str.push_back({ a,b });
		place.push_back({ i_a + j_a, i_b + j_b }); //i号点 到 j号点 
		//cout << i_a + j_a << " " << i_b + j_b << endl;
	}

	floyd();
	//print();
	for (int i = 0; i < place.size(); i++)
	{
		cout << "To get from " << str[i].first << " to " << str[i].second << " takes " << maze[place[i].first][place[i].second] << " knight moves." << endl;
	}
}
