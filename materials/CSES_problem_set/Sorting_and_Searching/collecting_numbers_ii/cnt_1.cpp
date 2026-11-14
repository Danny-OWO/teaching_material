#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    // 加上這兩行加速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, oper; 
    cin >> n >> oper;
    vector<ll> ins(n+1);
    vector<ll> nums(n+1);
    for (ll i = 0; i < n;  i++) {
        ll k; 
        cin >> k;
        ins[i+1] = k;
        nums[k] = i;
    }
    
    ll ans = 1;
    for (ll j = 1; j < n; j++) {
        if (nums[j] > nums[j + 1]) {
            ans++;
        }
    }
    
    for (ll j = 0; j < oper; j++)
    {
        ll a, b;
        cin >> a >> b;
        cout << "NIGGA" << endl;
        if (nums[ins[a-1]] > nums[ins[a]] && a > 1)
        {
            ans--;
        }
        if (nums[ins[a]] > nums[ins[a+1]] && a < n)
        {
            ans--;
        } 
        if (nums[ins[b-1]] > nums[ins[b]] && b>1)
        {
            ans--;
        }
        if (nums[ins[b]] > nums[ins[b+1]] &&b<n)
        {
            ans--;
        }

        if (nums[ins[a-1]] > nums[ins[b]] && a > 1)
        {
            ans++;
        } 
        if (nums[ins[b]] > nums[ins[a+1]] && a < n)
        {
            ans++;
        }
        if (nums[ins[b-1]] > nums[ins[a]] && b>1)
        {
            ans++;
        }
        if (nums[ins[a]] > nums[ins[b+1]] &&b<n)
        {
            ans++;
        }
    }
    cout << ans << endl;
}