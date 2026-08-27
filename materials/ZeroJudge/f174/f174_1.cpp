#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

int main()
{
    ll n, k;
    cin >> n >> k;

    vll pre;
    pre.push_back(0);

    ll s = 0;

    for (ll i = 0; i < n; i++)
    {
        ll x;
        cin >> x;

        s += x;
        pre.push_back(s);
    }

    deque<ll> dq;

    // 存的是 pre 的 index
    dq.push_back(0);

    ll max_score = 0;

    for (ll r = 1; r <= n; r++)
    {
        // 1. 太久以前的 index 丟掉
        while (!dq.empty() && dq.front() < r - k)
        {
            dq.pop_front();
        }

        // 2. front 就是目前最小的 pre
        ll dif = pre[r] - pre[dq.front()];

        if (dif > max_score)
        {
            max_score = dif;
        }

        // 3. 維護單調遞增
        while (!dq.empty() && pre[dq.back()] >= pre[r])
        {
            dq.pop_back();
        }

        dq.push_back(r);
    }

    cout << max_score << endl;
}