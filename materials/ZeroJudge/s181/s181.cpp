#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

ll n, m, r, k, t;
vector<ll> tal = {};

void dfs(ll pick, vector<ll> &players, vector<ll> &talent, vector<ll> &room, ll &ans)
{

    if (players.size() == k)
    {
        ans++;
        if (ans == t) 
        {
            for (ll i = 0; i < k; i++)
            {
                cout << players[i] << " ";
            }
            cout << "\n";
            exit(0); 
        }
        return; 
    }

    if (pick >= m*r)
    {
        return;
    }
    

    if (ans == t)
    {
        for (ll i = 0; i < k; i++)
        {
            cout << players[i] << " ";
        }
        cout << "\n";
        exit(0);
    }
    else
    {

        ll number = pick+1;
        //cout << number << endl;
        ll special = tal[pick];
        ll hisroom = pick/r+1;
        
        if (talent[special] != 1 && room[hisroom] < 2)
        {
            players.pb(number);
            talent[special] = 1;
            room[hisroom]++;
            dfs(pick+1, players, talent, room, ans);
            players.pop_back();
            talent[special] = 0;
            room[hisroom]--;
        }

        dfs(pick+1, players, talent, room, ans);
        return;
    }
    
    
}







int main()
{
    
    cin >> n >> m >> r >> k >> t;


    ll _ = m*r;
    for (ll i = 0; i < _; i++)
    {
        ll o; cin >> o;
        tal.pb(o);
    }
    
    vector<ll> players = {};
    vector<ll> talent(n+1, 0);
    vector<ll> room(m+1, 0);
    ll ans = 0;

    dfs(0, players, talent, room, ans);

}