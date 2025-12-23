#include<iostream>
#include<queue>
#include<unordered_map>
#include<iomanip>

using namespace std;
string alp;
unordered_map<char, int> mp;

void huffman(int & lat)
{
    
    for(int i = 0; i < alp.size(); i++)
    {
        mp[alp[i]]++;
    }
    priority_queue<int, vector<int>, greater<int> > q;
    for(auto c: mp)
    {
        q.push(c.second);
    }

    //所有非叶子节点的权值之和就是编码的长度。

    //特判1，因为1不进入while
    if(q.size() == 1) lat += q.top();
    while(q.size() > 1)
    {
        int a = q.top(); q.pop();
        int b = q.top(); q.pop();
        lat += (a+b);
        q.push(a+b);
    }
    
    mp.clear();

    return ;
}

int main()
{
    while(cin>>alp && alp != "END")
    {
        int bef = 8 * alp.size();
        int lat = 0;
        huffman(lat);
        cout << bef << " "; 
        cout<< lat <<" ";
        cout<<fixed<<setprecision(1)<<bef/(lat*1.0)<<endl;
    }
    return 0;
}
