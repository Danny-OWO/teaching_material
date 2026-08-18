#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

void out(vector<vector<ll>> &maxtrix)
{
    //cout << "PRINT" << endl;
    for (ll i =0; i < maxtrix.size(); i++)
    {
        for (ll j = 0; j < maxtrix[i].size(); j++)
        {
            if (j != maxtrix[i].size()-1)
            {
                cout << maxtrix[i][j] << " ";
            }
            else
            {
                cout << maxtrix[i][j];
            }
            
        }
        cout << "\n";
    }
    //cout << "PRINT" << endl;
}




void spin(vector<vector<ll>> &maxtrix, ll &r, ll &c)
{
    vector<vector<ll>> y;

    for (ll j = 0; j < c; j++)
    {
        vector<ll> p = {};
        for (ll i = r-1; i >= 0; i--)
        {
            p.pb(maxtrix[i][j]);
        }
        y.pb(p);
    }

    ll temp = c;
    c = r;
    r = temp;
    maxtrix = y; 
    //out(maxtrix);
}


void flip(vector<vector<ll>> &maxtrix, ll &r, ll &c)
{
    vector<vector<ll>> y;

    for (ll j = r-1; j >= 0; j--)
    {
        vector<ll> p = maxtrix[j];
        y.pb(p);
    }

    maxtrix = y; 
    //out(maxtrix);
}






int main()
{
    vector<vector<ll>> matrix;
    ll r, c, m;
    cin >> r >> c >> m;
    for (ll i = 0; i < r; i++)
    {
        vector<ll> rrr = {};
        for (ll j = 0; j < c; j++)
        {
            ll o; cin >> o;
            rrr.pb(o);
        }
        matrix.pb(rrr);

    }

    vector<ll> oper = {};
    for (ll x = 0; x < m; x++)
    {
        ll www;
        cin >> www;
        oper.pb(www);
    }


    for (ll o = m-1; o >= 0; o--)
    {
        ll k = oper[o];
        if (k == 0)
        {
            //cout << "spin" << endl;
            spin(matrix, r, c);
            spin(matrix, r, c);
            spin(matrix, r, c);
        }
        else
        {
            //cout << "flip" << endl;
            flip(matrix, r, c);
        }
    }
    cout << r << " " << c << endl;
    out(matrix);
    
}






/*
3 2 3
1 1
3 1
1 2
1 0 0




*/