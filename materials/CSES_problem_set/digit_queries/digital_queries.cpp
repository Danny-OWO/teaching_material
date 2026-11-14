#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll check(ll k, ll b, ll i)
{
    k -= 9 * b * i;
    b *= 10;

    if (k < 0)
    {
        return i;
    }
    else if (k == 0)
    {
        return -1;
    }
    else
    {
        return check(k,b,i+1);
    }

}


void ans(ll g, ll k)
{
    if (g == -1)
    {
        cout << 0 << endl;
        return;
    }
    ll b = 1;
    for (ll j = 1; j < g; j++)
    {
        k -= 9 * b * j;
        b *= 10;
    }
    string x = to_string(b + ((k-1) / g));
    cout << x[(k - 1) % g] << endl;

}


int main()
{
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++)
    {
        ll k;
        cin >> k;
        ans(check(k, 1, 1), k);
    }
}