#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

vector<ll> a;
vector<ll> b;

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;
    for (ll i = 0; i < n; i++)
    {
        ll g;
        cin >> g;
        a.pb(g);
    }
    for (ll i = 0; i < m; i++)
    {
        ll g;
        cin >> g;
        b.pb(g);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll i = 0;
    ll j = 0;
    ll ans = 0;

    while (i < a.size() && j < b.size())
    {
        ll tar = a[i];
        ll hou = b[j];

        if (hou < tar - k)
        {
            j++;
        }
        else if (hou > tar + k)
        {
            i++;
        }
        else
        {
            ans++;
            i++;
            j++;
        }


    }



    cout << ans << endl;
}