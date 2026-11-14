#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s = {};
string ans = "";
ll counts[26] = {0};
ll len = 0;
int pre = -1;
int check()
{
    int index = -1;
    for (int i = 0; i < 26; i++)
    {   
        if (2 * counts[i] == len + 1)
        {
            pre = i;
            counts[i] -= 1;
            return i;
            
        }

        if (2 * counts[i] > len + 1)
        {
            return -1;
        }

        if (index == -1 && counts[i] != 0 && i != pre)
        {
            index = i;
        }

    }
    if (index == -1)
    {
        return -1;
    }
    pre = index;
    counts[index] -= 1;
    return index;
}




int main()
{
    
    cin >> s;
    len = s.size();
    for (ll i = 0; i < s.size(); i++)
    {
        counts[char(s[i])-65] += 1;
    }

    for (ll i = 0; i < s.size(); i++)
    {
        int x = check();
        if (x == -1)
        {
            cout << -1 << endl;
            return 0;
        }
        len -= 1;
        ans += char(x+65);
    }

    cout << ans << endl;
}
