#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

ll check()
{
    stack<ll> s;
    string word;
    cin >> word;
    ll ans = 0;
    for (ll j = 0; j < word.size(); j++)
    {
        char cur = word[j];
        if (cur == '(')
        {
            s.push(1);
        }
        else
        {
            if (s.empty())
            {
                cout << 0 <<  endl;
                return 0;
            }
            else
            {
                s.pop();
                ans++;
            }
        }
    }
    if (s.empty())
    {
        cout << ans << endl;
    }
    else
    {
        cout << 0 << endl;
    }
    
    return 0;
}




int main()
{
    ll n;
    cin >> n;
    
    for (ll i = 0; i < n; i ++)
    {
        check();
    }
}