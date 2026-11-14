#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

ll n, m;
vector<ll> nums;

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
    cin >> n >> m;
    ll ans = 0;
    ll temp = -1;
    for (ll i = 0; i < n; i++)
    {
        ll k;
        cin >> k;
        nums.pb(k);
        if (k < temp)
        {
            ans++;
        }
        temp = k;
    }
    //cout << ans << endl;

    for (ll o = 0; o < m; o++)
    {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        
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
        set<pair<ll,ll>> sss(step.begin(), step.end());
        step.assign(sss.begin(), sss.end());


        for (ll x = 0; x < step.size(); x++)
        {
            ll t1 = nums[step[x].first];
            ll t2 = nums[step[x].second];

            ans -= check(t1,t2);
        }



        ll temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
        
        for (ll x = 0; x < step.size(); x++)
        {
            ll t1 = nums[step[x].first];
            ll t2 = nums[step[x].second];

            ans += check(t1,t2);
        }
        cout << ans << endl;
    }
}



