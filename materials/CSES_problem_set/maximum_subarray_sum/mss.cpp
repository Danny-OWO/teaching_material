#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
 
int main()
{
    ll n; cin >> n;
    vector<ll> k = {};
    ll s = 0;
    k.pb(0);
    for (ll i =0; i < n; i++)
    {
        ll m; cin >> m;
        s += m;
        k.pb(s);
    }
    auto max_index = max_element(k.begin(), k.end());
    ll MM = *max_index;
    ll mm = *min_element(k.begin(), max_index+1);
    
    if (MM == 0)
    {
        k.erase(k.begin());
        cout << k[0] << endl;
        ll tt = *max_element(k.begin(), k.end());
        cout << tt << endl;
    }
    else
    {
        if (MM-mm < 0)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << MM- mm << endl;
        }
    }
}
