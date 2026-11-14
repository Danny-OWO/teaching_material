#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using ll = long long;
#define pb push_back

ll check(ll a, ll b)
{
    // Returns 1 if value 'a' appears later in the array than value 'b'
    if (a > b)
    {
        return 1;
    }
    return 0;
}

int main()
{
    ll n, m; cin >> n >> m;
    vector<ll> nums(n+2); // Acts as our pos[] array (value -> index)
    vector<ll> realnum;   // Acts as our standard array (index -> value)
    
    // We can use 0-indexed values internally to make things cleaner
    for (ll i = 0; i < n; i++)
    {
        ll k; cin >> k;
        nums[k] = i;      // Store position of value k
        realnum.pb(k);    // Store value k at index i
    }
    
    ll ans = 1;
    for (ll j = 1; j < n; j++)
    {
        if (nums[j] > nums[j+1])
        {
            ans++;
        }
    }
    
    for (ll p = 0; p < m; p++)
    {
        ll a, b;
        cin >> a >> b;
        a--; b--; // Convert queries to 0-based indices
        
        if (a == b) {
            cout << ans << "\n";
            continue;
        }

        ll v1 = realnum[a];
        ll v2 = realnum[b];

        // FIX 1: We populate step with adjacent VALUES, not indices!
        vector<pair<ll,ll>> step;
        if (v1 > 1) step.pb({v1 - 1, v1});
        if (v1 < n) step.pb({v1, v1 + 1});
        if (v2 > 1) step.pb({v2 - 1, v2});
        if (v2 < n) step.pb({v2, v2 + 1});

        // Deduplicate pairs in case v1 and v2 are consecutive numbers
        set<pair<ll ,ll>> sss(step.begin(), step.end());
        step.assign(sss.begin(), sss.end()); // FIX 2: Fixed typo (.assert -> .assign)

        // Subtract old inversions
        for (ll g = 0; g < step.size(); g++)
        {
            // step[g].first is value X, step[g].second is value X+1
            ans -= check(nums[step[g].first], nums[step[g].second]);
        }

        // FIX 3: Swap values and their tracked positions cleanly
        swap(nums[v1], nums[v2]);
        swap(realnum[a], realnum[b]);

        // Add new inversions
        for (ll g = 0; g < step.size(); g++)
        {
            ans += check(nums[step[g].first], nums[step[g].second]);
        }
        
        cout << ans << "\n";
    }
    return 0;
}