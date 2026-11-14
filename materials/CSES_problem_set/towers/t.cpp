#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n; cin >> n;
    vector<ll> nums;
    vector<ll> towers;
    for (ll i = 0; i < n; i++)
    {
        ll p; cin >> p;
        nums.pb(p);
    }

    towers.pb(nums[0]);
    for (ll j = 1; j < n; j++)
    {
        auto it = upper_bound(towers.begin(), towers.end(), nums[j]);

        if (it != towers.end())
        {
            *it = nums[j];
        }
        else
        {
            towers.pb(nums[j]);
        }
    }

    cout << towers.size() << endl;
}