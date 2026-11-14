#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n; cin >> n;
    vector<ll> k = {};

    for (ll i = 0; i < n; i++)
    {
        ll o; cin >> o;
        k.pb(o);
    }

    ll ans = 1;
    for (ll j = 1; j < n; j++)
    {
        if (k[j] < k[j-1])
        {
            ans++;
        }
    }
    cout << ans << endl;
}
