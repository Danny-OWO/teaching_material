#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
    ll n; cin >> n;
    queue<ll> q;
    for (ll i = 0; i < n; i++)
    {
        ll move; cin >> move;
        
        if (move == 1)
        {
            ll x; cin >> x;
            q.push(x);
        }
        else if (move == 2)
        {
            if (q.empty())
            {
                cout << -1 << endl;
            }
            else
            {
                cout << q.front() << endl;
            }
        }
        else if (move == 3 && !q.empty())
        {
            q.pop();
        }

    }
}