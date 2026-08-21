#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll r, c;
    cin >> r >> c;

    vector<vector<ll>> lst;
    vector<vector<ll>> pic;

    for (ll i = 0; i < r; i++)
    {
        vector<ll> o;
        for (ll j = 0; j < c; j++)
        {
            ll k;
            cin >> k;
            o.pb(k);
        }
        lst.pb(o);
    }

    for (ll i = 0; i < r; i++)
    {
        vector<ll> o;
        for (ll j = 0; j < c; j++)
        {
            ll k;
            cin >> k;
            o.pb(k);
        }
        pic.pb(o);
    }

    vector<ll> situ = {0, 0, 0, 0};



    for (ll i = 0; i < r; i++)
    {
        for (ll j = 0; j < c; j++)
        {
            // 0°
            if (lst[i][j] == pic[i][j])
                situ[0]++;

            // 180°
            if (lst[i][j] == pic[r - 1 - i][c - 1 - j])
                situ[1]++;

            if (r == c)
            {
                // 90°
                if (lst[i][j] == pic[r - 1 - j][i])
                    situ[2]++;

                // 270°
                if (lst[i][j] == pic[j][c - 1 - i])
                    situ[3]++;
            }
        }
    }

    ll ans = *max_element(situ.begin(), situ.end());

    cout << ans * 100 / (r * c) << "%" << endl;
}