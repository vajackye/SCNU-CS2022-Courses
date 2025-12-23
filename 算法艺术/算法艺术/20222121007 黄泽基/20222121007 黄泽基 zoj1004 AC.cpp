#include<iostream>
#include<unordered_map>
#include<stack>

using namespace std;
const int N = 1e5+10;
unordered_map<char, int> mp;
stack<char> st;
string a, b;
char c[N];

void dfs(int cidx, int alen, int blen)
{
    if(cidx == b.size() * 2)
    {
        for(int i = 0; i < cidx; i++)
            cout<<c[i] << " ";
        cout << endl;
    }

    //入栈,不出栈, NO -> alen < a.size()-1,because：next dfs already add 1
    if(alen < a.size())
    {
        st.push(a[alen]); //入栈序列
        c[cidx] = 'i'; //入栈
        dfs(cidx + 1, alen + 1, blen);
        //回溯,idx不管，出栈覆盖
        st.pop();
    }

    //出栈 不入栈，前提满足条件~
    if(st.size() && st.top() == b[blen])
    {
        st.pop();
        c[cidx] = 'o';
        dfs(cidx + 1, alen, blen + 1);
        st.push(b[blen]); //回溯
    }
    return ;
}

int main()
{
    while(cin >> a >> b)
    {
        for(int i = 0; i < a.size(); i ++)
            mp[a[i]]++;
        for(int i = 0; i < b.size(); i ++)
            mp[b[i]]--;

        //剪枝
        bool fg = false;
        for(auto c : mp)
            if(c.second != 0)
            {
                cout<<'['<<endl<<']'<<endl;
                mp.clear();
                fg = true;
                break;
            }
        if(fg) continue;
        //开搜！      
        cout<<'['<<endl;
        dfs(0, 0, 0);
        cout<<']'<<endl;
    }
    return 0;
}
