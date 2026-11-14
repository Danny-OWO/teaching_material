#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define vl vector<ll>

vl apples;
ll sum = 0;
ll ans = LLONG_MAX;
ll n;

void dfs(ll depth, ll s)
{
    if (depth == n)
    {
        ans = min(ans, abs(s * 2 - sum));
        return; 
    }

    dfs(depth + 1, s);
    dfs(depth + 1, s + apples[depth]);

}




int main()
{

    cin >> n;

    for (ll i = 0; i < n; i++)
    {
        ll k; cin >> k;
        apples.pb(k);
        sum += k; // by using sum , we just need sum of one grounp(???) and then we can calculate the difference between those two groups (abs(2??? - s))
    }

    dfs(0,0);
    
    cout << ans << endl;
}