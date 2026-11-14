#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n, m;
    cin >> n >> m;
    set<ll> lightloc;
    multiset<ll> length;
    length.insert(n);
    for (ll i = 0; i < m; i++)
    {
        ll nw;
        cin >> nw;

        auto left = upper_bound(lightloc.begin(), lightloc.end(), nw);
        auto right = lower_bound(lightloc.begin(), lightloc.end(), nw);
        lightloc.insert(nw);

        if (left == right && left == lightloc.end())
        {
            length.insert(nw);
            length.insert(n-nw);
            length.erase(n);
        }
        else if (left == lightloc.end())
        {
            ll star = *right;
            length.insert(star - nw);
            length.insert(nw);
            length.erase(star);
        }
        else if (right == lightloc.end())
        {
            ll star = *left;
            length.insert(nw - star);
            length.insert(n - nw);
            length.erase(n - star);
        }
        else
        {
            ll starl = *left;
            ll starr = *right;
            length.insert(nw - starl);
            length.insert(starr - nw);
            length.erase(starr - starl);
        }

        cout << *length.rbegin() << endl;
    }
}