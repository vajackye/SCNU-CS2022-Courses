//每放置一个，就扫一行/一列，如果遇到墙壁，则停止扫描
//也即可再次放置。爆搜即可，
#include<iostream>

using namespace std;
const int N = 6;
char maze[N][N];
bool vis[N][N]; //行列计算公式？
int number = -1;
int n;
int pos = 0;

int dir[4][2] =
{
    {0,1},{1,0},{0,-1},{-1,0}
};

bool check(int x, int y)
{
    for (int i = x - 1; i >= 0; i--) //行检测炮楼,上检测。下必无
    {
        if (vis[i][y]) return false; //已有炮楼
        if (maze[i][y] == 'X') break; //wall阻挡，无敌
    }
    for (int j = y - 1; j >= 0; j--)
    {
        if (vis[x][j]) return false; //已有炮楼
        if (maze[x][j] == 'X') break; //wall
    }
    return true; //完美安全
}

void dfs(int pos, int num)
{
    //最后一个点搜索完毕
    if (pos == n * n)
    {
        number = max(number, num);
        return;
    }

    int sx = pos / n; //当前位置x
    int sy = pos % n; //当前位置y

    if (maze[sx][sy] == '.' && check(sx, sy))
    {
        vis[sx][sy] = true; //进入
        dfs(pos + 1, num + 1); //下一个格子搜索，并放入炮楼
        vis[sx][sy] = false; //回溯，不放炮楼
    }

    dfs(pos + 1, num); //不放炮楼
}

int main()
{
    while (cin >> n && n != 0)
    {
        number = -1;
        pos = 0; //检查是否都遍历过了每个点
        for (int i = 0; i < n; i++)
            cin >> maze[i];

        dfs(0, 0);
        cout << number << endl;
    }

}
