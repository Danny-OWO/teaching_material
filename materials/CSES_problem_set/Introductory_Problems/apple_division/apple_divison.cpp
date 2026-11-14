#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans = LLONG_MAX;
ll n;

void dfs(vector<ll> &w, ll i, ll &sum, ll cur)
{
    if (i == n)
    {
        ans = min(ans, abs(sum - cur * 2));
        return;
    }

    dfs(w,i+1,sum,cur);
    dfs(w,i+1,sum,cur + w[i]);
}





int main()
{
    ll sum = 0;
    cin >> n;

    vector<ll> w={};
    for (ll i = 0; i < n; i ++)
    {
        ll x;
        cin >> x;
        w.push_back(x);
        sum += x;
    }

    dfs(w,0,sum,0);

    cout << ans << endl;
}
