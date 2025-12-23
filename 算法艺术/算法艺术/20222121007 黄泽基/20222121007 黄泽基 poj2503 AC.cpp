#include<map>
#include<iostream>
#include<string>

using namespace std;
map<string, string> mp;

int main()
{
    string all;
    while(getline(cin, all) && !all.empty())
    {
        string a, b;
        int p = 0;
        for(int i = 0; i < all.size(); i++)
        {
            if(all[i] == ' ') break;
            a += all[i];
            p++;
        }
        p++;
        for(int i = p; i < all.size(); i++)
        {
            b += all[i];
        }
        mp[b] = a;
    }
    
    string ask;
    while(getline(cin, ask) && !ask.empty())
    {
        if(mp.find(ask) == mp.end()) cout<<"eh"<<endl;
        else cout<<mp[ask]<<endl;
    }
    
    return 0;
}
