#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 755

struct UnionFind {
    int x, y;
    int w;
};

UnionFind e[MAX * MAX / 2];
int w[MAX], father[MAX];

int cmp(const UnionFind &a, const UnionFind &b) {
    return a.w < b.w;
}

void MakeSet(int x) {
    father[x] = x;
    w[x] = 0;
}

int Find(int x) {
    if (x != father[x])
        father[x] = Find(father[x]);
    return father[x];
}

void Union(int x, int y, int weight) {
    if (w[x] > w[y]) 
        father[y] = x;
    else {
        father[x] = y;
        if (w[x] == w[y])  
            w[y]++;
    }
}

void Kruskal(int point_amount, int edge_amount) {
    sort(e, e + edge_amount, cmp);
    for (int i = 0; i < edge_amount; i++) {
        int x = Find(e[i].x);
        int y = Find(e[i].y);
        if (x != y) {
            Union(x, y, e[i].w);
            cout << e[i].x + 1 << " " << e[i].y + 1 << endl;
        }
    }
}

int main() {
    int T, N, M, cnt, s, t;
    int a[MAX], b[MAX];
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> a[i] >> b[i];
            MakeSet(i);
        }
        cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                e[cnt].x = i;
                e[cnt].y = j;
                e[cnt].w = (a[i] - a[j]) * (a[i] - a[j]) + (b[i] - b[j]) * (b[i] - b[j]);
                cnt++;
            }
        }
        cin >> M;
        for (int i = 0; i < M; i++) {
            cin >> s >> t;
            s--;
            t--;
            s = Find(s);
            t = Find(t);
            Union(s, t, 0);
        }
        Kruskal(N, cnt);
        if (T) cout << endl;
    }
    return 0;
}

