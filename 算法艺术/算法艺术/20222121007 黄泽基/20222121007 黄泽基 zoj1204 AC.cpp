#include<iostream>
#include<unordered_map>
#include<queue>
#include<stack>
#include<unordered_set>
#include<algorithm>
#include<string>

using namespace std;
const int N = 40;
int a[N], n;
unordered_set<int> st;
vector<string> ans;

void dfs(int idx, int sum, string ss, int nowl ,int level) //层数
{
	if (idx == n - 1) return;
	if (nowl >= level)
	{
		if(st.find(sum) != st.end()) //存在该数字
			ans.push_back(ss + "=" + to_string(sum));
		return;
	}
	if (sum > a[n - 1]) return; //不存在该结果

	for (int i = idx + 1; i < n - 1; i++)
	{
		string tmp = ss + "+" + to_string(a[i]);
		dfs(i, sum + a[i], tmp, nowl + 1, level);
	}
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
			st.insert(a[i]); //哈希查询
		}
		sort(a, a + n); //排序

		for (int len = 2; len <= n; len++) //长度限制
		{
			string ss = "";
			for (int i = 0; i < n - 1; i++) //dfs
			{
				ss += to_string(a[i]);
				dfs(i, a[i], ss, 1, len);
				ss = "";
			}
		}

		if (!ans.size()) cout << "Can't find any equations." << endl;
		for (auto c : ans) cout << c << endl;
		cout << endl;
		ans.clear();
		st.clear();
	}
	return 0;
}
