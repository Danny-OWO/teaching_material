// Kadane's Algorithm

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
        ll o; cin >> o;
        nums.pb(o);
    }

    ll result = nums[0];
    ll maxsumhere = nums[0];
    for (ll j = 1; j < n; j++)
    {
        maxsumhere = max(nums[j], maxsumhere+nums[j]);
        result = max(result, maxsumhere);
    }

    cout << result << endl;
}