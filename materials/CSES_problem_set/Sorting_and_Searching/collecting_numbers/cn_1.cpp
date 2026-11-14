#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main()
{
    ll n; cin >> n;
    vector<ll> nums(n+1);
    for (ll i = 0; i < n; i++)
    {
        ll k; cin >> k;
        nums[k] = i;
    }
    ll ans = 1;
    for (ll j = 1; j < n; j ++)
    {
        if (nums[j] > nums[j+1])
        {
            ans++;
        }
    }
    
    cout << ans << endl;
}
