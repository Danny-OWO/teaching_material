#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> w = {};
    for (ll i = 0; i < n; i++)
    {
        ll o; cin >> o; w.pb(o);
    }

    sort(w.begin(), w.end());
    ll ans = 0;
    ll i = 0, j = w.size()-1;

    while (i <= j)
    {
        if (i == j)
        {
            ans++;
            i++;
        }
        else
        {
            if (w[i] + w[j] <= k)
            {
                ans++;
                i++;
                j--;
            }
            else
            {
                ans++;
                j--;
            }
        }
    }
    cout << ans << endl;
}