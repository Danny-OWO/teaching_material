#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back

vector<vector<pair<ll,ll>>> x_based(30001);
vector<vector<pair<ll,ll>>> y_based(60001);

int main()
{
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++)
    {
        ll xx, yy, tt;
        cin >> xx >> yy >> tt;

        // 固定 x，按照 y 排列
        x_based[xx].pb({yy, tt});

        // 固定 y，按照 x 排列
        y_based[yy + 30000].pb({xx, tt});
    }

    // 一次 sort 就好
    for (auto &v : x_based)
        sort(v.begin(), v.end());

    for (auto &v : y_based)
        sort(v.begin(), v.end());


    ll ans = 0;

    char face = 'r';

    ll x = 0;
    ll y = 0;

    while (true)
    {
        // --------------------
        // right
        // --------------------
        if (face == 'r')
        {
            auto &v = y_based[y + 30000];

            ll ub = upper_bound(v.begin(), v.end(), make_pair(x, LLONG_MAX)) - v.begin();

            if (ub == v.size())
            {
                cout << ans << '\n';
                return 0;
            }

            x = v[ub].first;
            ll type = v[ub].second;

            ans++;

            if (type == 1) // "\"
                face = 'd';
            else           // "/"
                face = 'u';
        }

        // --------------------
        // left
        // --------------------
        else if (face == 'l')
        {
            auto &v = y_based[y + 30000];

            ll lb = lower_bound(v.begin(), v.end(), make_pair(x, LLONG_MIN)) - v.begin();

            if (lb == 0)
            {
                cout << ans << '\n';
                return 0;
            }

            lb--;

            x = v[lb].first;
            ll type = v[lb].second;

            ans++;

            if (type == 1) // "\"
                face = 'u';
            else           // "/"
                face = 'd';
        }

        // --------------------
        // up
        // --------------------
        else if (face == 'u')
        {
            auto &v = x_based[x];

            ll ub = upper_bound(v.begin(),v.end(),make_pair(y, LLONG_MAX)) - v.begin();

            if (ub == v.size())
            {
                cout << ans << '\n';
                return 0;
            }

            y = v[ub].first;
            ll type = v[ub].second;

            ans++;

            if (type == 1) // "\"
                face = 'l';
            else           // "/"
                face = 'r';
        }

        // --------------------
        // down
        // --------------------
        else if (face == 'd')
        {
            auto &v = x_based[x];

            ll lb = lower_bound(v.begin(), v.end(), pair<ll,ll>{y, LLONG_MIN}) - v.begin();

            if (lb == 0)
            {
                cout << ans << '\n';
                return 0;
            }

            lb--;

            y = v[lb].first;
            ll type = v[lb].second;

            ans++;

            if (type == 1)
                face = 'r';
            else
                face = 'l';
        }
    }
}