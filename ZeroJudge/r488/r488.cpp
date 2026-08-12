#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll r,c,d;
    cin >> r >> c >> d;
    vector<vector<pair<ll,ll>>> dino;
    for (ll i =0; i < r; i++)
    {
        vector<pair<ll,ll>> _ = {};
        for (ll j = 0; j < c; j++)
        {
            _.pb({0, d});
        }
        dino.pb(_);
    }
    
    ll k;
    cin >> k;

    for (ll j = 0; j < k; j++)
    {
        ll a, b;
        cin >> a >> b;
        dino[a][b].first++;
    }

    ll move;
    cin >> move;

    for (ll p = 0; p < move; p++)
    {
        ll a,b,s,d;
        cin >> a >> b >> s >> d;
        ll length = ((s-1)/2);
        ll killed = 0;
        bool key = false;
        for (ll delta1 = -length; delta1 <= length; delta1++)
        {
            for (ll delta2 = -length; delta2 <= length; delta2++)
            {
                ll t_x, t_y;
                t_x = b+delta2;
                t_y = a+delta1;

                if (0 <= t_x && t_x < c && 0 <= t_y && t_y < r)
                {
                    if (dino[t_y][t_x].first != 0)
                    {
                        killed += dino[t_y][t_x].first;
                        //cout << killed << endl;
                        dino[t_y][t_x].first = 0;
                        key = true;
                    }
                }
            }
        }
        k -= killed;
        if (key == false)
        {
            for (ll delta1 = -length; delta1 <= length; delta1++)
            {
                for (ll delta2 = -length; delta2 <= length; delta2++)
                {
                    ll t_x, t_y;
                    t_x = b+delta2;
                    t_y = a+delta1;

                    if (0 <= t_x && t_x < c && 0 <= t_y && t_y < r)
                    {
                        dino[t_y][t_x].second -= d;
                    }
                }
            }
        }
    }

    ll mxh = dino[0][0].second;
    ll mnh = d;

    for (ll i = 0; i < r; i++)
    {
        for (ll j = 0; j < c; j++)
        {
            if (dino[i][j].second > mxh)
            {
                mxh = dino[i][j].second;
            }
            if (dino[i][j].second < mnh)
            {
                mnh = dino[i][j].second;
            }
        }
    }

    cout << mxh << " " << mnh << " " << k;

}