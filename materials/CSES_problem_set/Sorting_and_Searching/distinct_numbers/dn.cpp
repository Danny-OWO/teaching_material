#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
int main()
{
    ll n;
    vector<ll> num = {};
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        ll k;
        cin >> k;
        num.pb(k);
    }

    sort(num.begin(), num.end());

    ll count = 0;
    ll holder = 0;

    for (ll i =0; i < n; i++)
    {
        if (num[i] != holder)
        {
            count += 1;
            holder = num[i];
        }
    }
    cout << count << endl;
}