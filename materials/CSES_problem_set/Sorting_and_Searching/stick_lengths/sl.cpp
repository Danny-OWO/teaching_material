#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n;
    cin >> n;

    vector<ll> nums = {};
    for (ll i =0; i < n; i++)
    {
        ll k; cin >> k;
        nums.pb(k);
    }

    sort(nums.begin(), nums.end());

    ll x = nums[nums.size() / 2] ;
    ll ans = 0;
    for (ll j = 0; j < n; j++)
    {
        ans += abs(x - nums[j]);
    }
    cout << ans << endl;
}