#include <bits/stdc++.h>
using namespace std;
using ll = long long;



ll check(ll a, ll b)
{
    if (a > b)
    {
        return 1;
    }
    return 0;
}


int main()
{
    ll n, m; cin >> n >> m;
    vector<ll> nums(n+1);
    vector<ll> realnum;
    for (ll i = 0; i < n; i++)
    {
        ll k; cin >> k;
        nums[k] = i;
        realnum.pb(k);
    }
    ll ans = 1;
    for (ll j = 1; j < n; j ++)
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
        a--;
        b--;
        
        vector<pair<ll,ll>> step;

        if (a == 0)
        {
            step.pb({0,1});
        }
        else
        {
            step.pb({a-1,a});
            step.pb({a,a+1});
        }
        if (b == n-1)
        {
            step.pb({n-2,n-1});
        }
        else
        {
            step.pb({b-1,b});
            step.pb({b,b+1});
        }

        set<pair<ll ,ll>> sss(step.begin(), step.end());
        step.assign(sss.begin(), sss.end());

        for (ll g =0; g < step.size(); g++)
        {
            ans -= check(nums[realnum[step[g].first]], nums[realnum[step[g].second]]);
        }

        ll temp = nums[realnum[step[g].first]];
        nums[realnum[step[g].first]] = nums[realnum[step[g].second]];
        nums[realnum[step[g].second]] = temp;

        temp = realnum[a];
        realnum[a] = realnum[b];
        realnum[b] = temp;

        for (ll g =0; g < step.size(); g++)
        {
            ans += check(nums[realnum[step[g].first]], nums[realnum[step[g].second]]);
        }
        cout << ans << endl;
    }
}
