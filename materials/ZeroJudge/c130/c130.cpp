#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<ll>> ans = {};

void print(const vector<ll> &picks)
{
    vector<ll> sorted = picks;
    sort(sorted.rbegin(), sorted.rend());
    for (ll i = 0; i < sorted.size(); i++)
    {
        if (i == 0)
        {
            cout << sorted[i];
        }
        else
        {
            cout << '+' << sorted[i];
        }
    }
    cout << '\n';
}



void dfs(ll t, ll n, vector<ll> &nums, vector<ll> &picks, ll i, ll s)
{
    if (s == t)
    {
        vector<ll> solution = picks;
        sort(solution.rbegin(), solution.rend());
        ans.push_back(solution);
        return;
    }
    
    if (s > t)
    {
        return;
    }
    
    if (i == n)
    {
        return;
    }

    dfs(t,n,nums,picks,i+1,s);
    picks.push_back(nums[i]);
    s += nums[i];
    dfs(t,n,nums,picks,i+1,s);
    picks.pop_back();
}







int main()
{
    while (true)
    {
        ll t; cin >> t;
        ll n; cin >> n;
        if (n == 0)
        {
            break;
        }

        vector<ll> nums = {};

        for (ll i =0; i < n; i++)
        {
            ll o; cin >> o;
            nums.push_back(o);
        }
        vector<ll> picks;
        sort(nums.begin(), nums.end());
        dfs(t, n, nums, picks, 0, 0);

        cout << "Sums of " << t  << ":" << endl;  
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        reverse(ans.begin(), ans.end());
        if (ans.empty())
        {
            cout << "NONE" << endl;
        }
        else
        {
            for (ll i = 0; i < ans.size(); i++)
            {
                print(ans[i]);
            }
        }
        ans.clear();
    }
}