#include<iostream>
#include<unordered_map>

using namespace std;
const int N = 1000;

unordered_map<char, int> mp =
{
    {'A', 0}, {'C', 1}, {'G',2}, {'T',3}
    ,{'-',4}
}; //矩阵映射

int sc[5][5] //分数矩阵
{
    5,-1,-2,-1,-3,-1,5,-3,-2,-4,-2,-3,5,
    -2,-2,-1,-2,-2,5,-1,-3,-4,-2,-1,0
};

int f[N][N];



int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        string s1, s2;
        cin >> n >> s1;
        cin >> m >> s2;

        f[0][0] = 0; //初始化
        for (int i = 1; i <= n; i++) //行初始化，用-标记。即第1串i个字符与第2串0个字符匹配，那么只有添加-
            f[i][0] = f[i - 1][0] + sc[mp[s1[i - 1]]][4];
        for (int j = 1; j <= m; j++) //列初始化，用-标记，同上
            f[0][j] = f[0][j - 1] + sc[4][mp[s2[j - 1]]];

        //最长公共子序列
        //注意：字符串的i-1，j-1是因为从0下标开始。其实是i ，j匹配
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                int t1 = f[i - 1][j] + sc[mp[s1[i - 1]]][4]; //串1匹配-值，
                int t2 = f[i][j - 1] + sc[4][mp[s2[j - 1]]]; //串2匹配-值
                int t3 = f[i - 1][j - 1] + sc[mp[s1[i - 1]]][mp[s2[j - 1]]]; //不匹配-
                f[i][j] = max(t3, max(t2, t1));
            }
        }

        cout << f[n][m] << endl;
    }
    return 0;
}
