#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<ll>> rotate90(vector<vector<ll>> a)
{
    ll r = a.size();
    ll c = a[0].size();

    vector<vector<ll>> result(c, vector<ll>(r));

    for (ll i = 0; i < r; i++)
    {
        for (ll j = 0; j < c; j++)
        {
            result[j][r - 1 - i] = a[i][j];
        }
    }

    return result;
}

ll compare(vector<vector<ll>>& a, vector<vector<ll>>& b)
{
    // 尺寸不一樣，不能直接疊在一起比較
    if (a.size() != b.size())
        return -1;

    if (a[0].size() != b[0].size())
        return -1;

    ll same = 0;

    for (ll i = 0; i < a.size(); i++)
    {
        for (ll j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == b[i][j])
            {
                same++;
            }
        }
    }

    return same;
}

int main()
{
    ll r, c;
    cin >> r >> c;

    vector<vector<ll>> lst(r, vector<ll>(c));
    vector<vector<ll>> pic(r, vector<ll>(c));

    for (ll i = 0; i < r; i++)
    {
        for (ll j = 0; j < c; j++)
        {
            cin >> lst[i][j];
        }
    }

    for (ll i = 0; i < r; i++)
    {
        for (ll j = 0; j < c; j++)
        {
            cin >> pic[i][j];
        }
    }

    // 儲存四種旋轉
    vector<vector<vector<ll>>> lst_rotate(4);
    vector<vector<vector<ll>>> pic_rotate(4);

    lst_rotate[0] = lst;
    pic_rotate[0] = pic;

    // 每次都把上一張再轉 90°
    for (ll i = 1; i < 4; i++)
    {
        lst_rotate[i] = rotate90(lst_rotate[i - 1]);
        pic_rotate[i] = rotate90(pic_rotate[i - 1]);
    }

    ll best = 0;

    // 4 × 4 = 16 種組合全部試
    for (ll a = 0; a < 4; a++)
    {
        for (ll b = 0; b < 4; b++)
        {
            ll same = compare(lst_rotate[a], pic_rotate[b]);

            if (same != -1)
            {
                best = max(best, same);
            }
        }
    }

    cout << best * 100 / (r * c) << "%" << endl;
}