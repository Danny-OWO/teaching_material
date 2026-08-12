#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n;
    cin >> n;

    vector<ll> lst = {};
    ll prev = 0;
    for (ll i = 0 ; i < n; i++)
    {
        ll o;
        cin >> o;
        lst.pb(o - prev);
        prev = o;
    }


    for (ll i =0; i < n; i ++)
    {
        cout << lst[i] << " ";
    }
}