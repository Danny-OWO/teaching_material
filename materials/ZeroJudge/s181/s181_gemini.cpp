#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

ll n, m, r, k, t;
vector<ll> tal = {};

void dfs(ll pick, vector<ll> &players, vector<ll> &talent, vector<ll> &room, ll &ans)
{
    // BASE CASE 1: Successfully formed a team of size k
    if (players.size() == k)
    {
        ans++; // We found exactly one distinct team combination
        
        if (ans == t)
        {
            for (ll i = 0; i < k; i++)
            {
                cout << players[i] << (i == k - 1 ? "" : " ");
            }
            cout << "\n";
            exit(0); // CRITICAL: Exits the whole program instantly so it prints only once!
        }
        return; // Stop looking deeper along this path
    }

    // BASE CASE 2: No more players left to pick from
    if (pick >= m * r)
    {
        return;
    }

    ll number = pick + 1;
    ll special = tal[pick];
    ll hisroom = pick / r + 1;
    
    // CHOICE 1: Try to PICK the current player (Prioritizing smaller numbers first)
    if (talent[special] != 1 && room[hisroom] < 2)
    {
        players.pb(number);
        talent[special] = 1;
        room[hisroom]++;
        
        dfs(pick + 1, players, talent, room, ans);
        
        // Backtrack
        players.pop_back();
        talent[special] = 0;
        room[hisroom]--;
    }

    // CHOICE 2: SKIP the current player
    dfs(pick + 1, players, talent, room, ans);
}

int main()
{
    // Optimize fast standard I/O operations for ZeroJudge
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> r >> k >> t)) return 0;

    ll total = m * r;
    for (ll i = 0; i < total; i++)
    {
        ll o; 
        cin >> o;
        tal.pb(o);
    }
    
    vector<ll> players = {};
    vector<ll> talent(n + 1, 0);
    vector<ll> room(m + 1, 0);
    ll ans = 0;

    dfs(0, players, talent, room, ans);

    return 0;
}
