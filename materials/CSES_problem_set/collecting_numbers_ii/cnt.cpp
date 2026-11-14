#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

void ans(vector<ll> &nums)
{
    ll ans = 1;
    for (ll i = 1; i < n; i++)
    {
        if (nums[i] > nums[i+1])
        {
            ans++;
        }
    }
    cout << ans << endl;
    return;
}





int main()
{
    ll n, oper; cin >> n >> oper;
    vector<ll> nums(n+1);

    for (ll i = 0; i < n; i ++)
    {
        ll k; cin >> k;
        nums[k] = i;
    }  

    for (ll j = 0; j < oper; j++)
    {
        ll a,b;
        cin >> a >> b;
        ll temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
        ans(nums);
    }


}