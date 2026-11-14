#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n; cin >> n;
    vector<pair<ll,ll>> movies = {};
    for (ll i = 0; i < n; i++)
    {
        ll k,p; cin >> k >> p;
        movies.pb({p,k});
    }
    sort(movies.begin(), movies.end());

    ll cur_t = 0;
    ll count = 0;

    for (ll j = 0; j < movies.size(); j ++)
    {
        if (movies[j].second >= cur_t)
        {
            count += 1;
            cur_t = movies[j].first;
        }
    }

    cout << count << "\n";

}