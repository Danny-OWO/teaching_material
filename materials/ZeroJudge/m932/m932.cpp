#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll r,c,g;
    cin >> r >> c >> g;

    vector<string> m;
    
    for (ll i = 0; i < r; i++)
    {
        string k; cin >> k;
        m.pb(k);
    }

    ll pos_r = r-1;
    ll pos_c = 0;

    vector<ll> delta_r = {1, 0, -1, -1, 0, 1};
    vector<ll> delta_c = {0, 1, 1, 0, -1, -1};

    vector<char> words; 
    for (ll mov = 0; mov < g; mov++)
    {
        ll move;
        cin >> move;
        ll new_pos_r = pos_r - delta_r[move];
        ll new_pos_c = pos_c + delta_c[move];

        if (new_pos_r > -1 && new_pos_r < r && new_pos_c > -1 && new_pos_c < c)
        {
            cout << m[new_pos_r][new_pos_c];
            words.pb(m[new_pos_r][new_pos_c]);
            pos_r = new_pos_r;
            pos_c = new_pos_c;
        }
        else
        {
            cout << m[pos_r][pos_c];
            words.pb(m[pos_r][pos_c]);
        }


    }

    set<char> s(words.begin(), words.end());
    vector<char> xxx(s.begin(), s.end());
    cout << "\n" << xxx.size() << endl;

}