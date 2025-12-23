#include <iostream>
#include <cmath>
#include <iomanip>
#include <queue>
using namespace std;

const int N = 210; // 修改为 210
int n;

struct s {
    int x, y;
} ans[N];

struct DIS {
    int x;
    int y;
    double dis;
};

struct Cmp {
    bool operator()(DIS &a, DIS &b) {
        return a.dis > b.dis;
    }
};

double Max;
double maze[N][N]; 
int p[N];

void init() {
    for(int i = 1; i <= n; i++) 
        p[i] = i;
}

int findParent(int x) { 
    return x == p[x] ? x : findParent(p[x]);
}

void merge(int x, int y) {
    x = findParent(x); y = findParent(y);
    if(x != y) p[x] = y;
}

double getDIS(int sx, int sy, int ex, int ey) {
    return sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));
}

void dijkstra() {
    priority_queue<DIS, vector<DIS>, Cmp> q; 
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            maze[i][j] = getDIS(ans[i].x, ans[i].y, ans[j].x, ans[j].y);
            maze[j][i] = maze[i][j];
            q.push({i, j, maze[i][j]});
        }
    }

    int cnt = 0;
    while(!q.empty() && cnt < n - 1) { 
        auto c = q.top();
        q.pop();
        if(findParent(1) == findParent(2)) return ; //提前终止。找到了 
        if(findParent(c.x) == findParent(c.y)) continue;
        Max = max(Max, c.dis);
        merge(c.x, c.y);
        cnt++;
    }  
}

int main() {
    int num = 1;
    while(cin >> n && n) {
        init();
        Max = -1.0;
        for(int i = 1; i <= n; i++)
            cin >> ans[i].x >> ans[i].y;
        dijkstra();
        cout << "Scenario #" << num++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << Max <<endl;
        cout<<endl;
    }
    return 0;
}

