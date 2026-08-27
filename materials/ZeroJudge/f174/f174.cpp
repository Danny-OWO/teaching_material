// 這板只有用一般的sliding window 而他不足以做這題 還需要 單調隊列
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
int main()
{
    ll n,k; cin >> n >> k;
    vector<ll> pre;
    ll s = 0;
    pre.pb(s);

    for (ll x = 0; x < n; x++)
    {
        ll m;
        cin >> m;
        pre.pb(s+m);
        s += m;
    }
    
    ll l = 0; 
    ll r = 0;
    ll max_score = 0;
    while (l <= r && r < n+1)
    {
        ll left = pre[l];
        ll right = pre[r];
        ll dif = right - left;
        
        if (dif > max_score)
        {
            max_score = dif;
        }

        if (r-l+1 == k+1)
        {
            l++;
        }
        else
        {
            r++;
        }
    }

    cout << max_score << endl;
}