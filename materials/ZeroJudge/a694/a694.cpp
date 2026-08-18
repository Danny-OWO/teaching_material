#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll n, m;    
    while (cin >> n >> m)
    {
        vector<vector<ll>> lst;
        vector<vector<ll>> madd(n, vector<ll>(n,0));
        for (ll i = 0; i < n; i++)
        {
            vector<ll> p = {};
            for (ll j = 0; j < n; j++)
            {
                ll k;
                cin >> k;
                p.pb(k);
            }
            lst.pb(p);
        }

        // -left-up+ upleft

        for (ll i = 0; i < n; i++)
        {
            vector<ll> p = {};
            for (ll j = 0; j < n; j++)
            {
                ll up = 0;
                ll left = 0;
                ll up_left = 0;
                if (i != 0)
                {
                    //cout << "?" << endl;
                    up = madd[i-1][j];
                }
                if (j != 0)
                {
                    //cout << "!" << endl;
                    //cout << i << " " << j << endl;
                    left = madd[i][j-1];
                }
                if (i != 0 && j != 0)
                {
                    //cout << "FFF" << endl;
                    up_left = madd[i-1][j-1];
                }
                //cout <<"OOO" << endl;
                madd[i][j] = (lst[i][j] + up + left - up_left);
            }
        }


        for (ll i = 0; i < m; i ++)
        {
            ll a, b, c, d;
            cin >> a >> b >> c >> d;
            a--; b--; c--; d--;
            if (a == 0 && b == 0)
            {
                cout << madd[c][d] << endl;
            }
            else if (a == 0)
            {
                cout << madd[c][d] - madd[c][b-1] << endl;
            }
            else if (b == 0)
            {
                cout << madd[c][d] - madd[a-1][d] << endl;           
            }
            else
            {
                cout << madd[c][d] - madd[a-1][d] - madd[c][b-1] + madd[a-1][b-1] << endl;
            }
            
        }
    }

}