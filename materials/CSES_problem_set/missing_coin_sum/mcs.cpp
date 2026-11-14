#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n; cin >> n;
    vector<ll> nums = {};
    for (ll i = 0; i < n; i++)
    {
        ll k; cin >> k; nums.pb(k);
    }
    sort(nums.begin(), nums.end());

    ll cur = 0;

    for (ll j = 0; j < n; j++)
    {
        if (nums[j] <= cur+1)
        {
            cur += nums[j];
        }
        else
        {
            cout << cur+1 << endl;
            return 0;
        }
    }
    cout << cur + 1 << endl;
    
}