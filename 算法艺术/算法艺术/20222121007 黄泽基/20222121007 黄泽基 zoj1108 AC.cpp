 #include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <stack>
using namespace std;
const int N = 1e5 + 10;
int f[N], p[N];
struct mcs
{
    int idx;
    int w;
    int sp;
}ans[N];

bool cmp(const mcs& a, const mcs& b)
{
    if (a.w != b.w) return a.w < b.w;
    return a.sp > b.sp;
}

int main()
{
    int cnt = 0;
    int a, b;
    while (cin >> a >> b)
    {
        ans[++cnt].w = a;
        ans[cnt].sp = b, ans[cnt].idx = cnt;
        p[cnt] = 0;
    }

    sort(ans + 1, ans + 1 + cnt, cmp); //sort,按题目严格上下。。抽象题目
    //memset(f, 1, sizeof f); //初始化1只
    int Mnum = 0, index = 0; //存最大值，以及相应下标。可通过并查集回溯路径输出
    for (int i = 1; i <= cnt; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (ans[i].w > ans[j].w && ans[i].sp < ans[j].sp )
            {
                if(f[i] < f[j] + 1)
                    p[i] = j; //链接保存前缀，简略版并查集
                f[i] = max(f[i], f[j] + 1);
            }
            if (Mnum < f[i]) Mnum = f[i], index = i;
        }
    }

    stack<int> st;
    while(index){
        st.push(index);
        index = p[index];
    }
    cout << Mnum << endl;
    while (st.size())
    {
        cout << ans[st.top()].idx<<endl;
        st.pop();
    }
    return 0;
}
