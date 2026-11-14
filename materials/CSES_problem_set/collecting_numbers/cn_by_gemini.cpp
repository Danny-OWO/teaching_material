#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    // 加上這兩行加速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; 
    cin >> n;
    
    vector<ll> nums(n + 1);
    for (ll i = 0; i < n; i++) {
        ll k; 
        cin >> k;
        nums[k] = i;
    }
    
    ll ans = 1;
    for (ll j = 1; j < n; j++) {
        if (nums[j] > nums[j + 1]) {
            ans++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}