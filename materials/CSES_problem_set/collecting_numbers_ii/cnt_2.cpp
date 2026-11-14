#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back


ll check(vector<ll> &nums, vector<ll> &ins, ll a, ll n)
{
    //cout << "000" << endl;
    ll delta = 0;
    if (a > 1)
    {
        //cout << "111" << endl;
        if (nums[ins[a-1]] > nums[ins[a]])
        {
            delta++;
        }
    }

    if (a < n)
    {
        //cout << "222" << endl;
        if (nums[ins[a]] > nums[ins[a+1]])
        {
            delta++;
        }
    }

    return delta;
}




int main()
{   
    ll n, oper;
    cin >> n >> oper;
    vector<ll> ins(n+1);
    vector<ll> nums(n+1);
    for (ll i = 0; i < n;  i++) {
        ll k; 
        cin >> k;
        ins[i+1] = k;
        nums[k] = i;
    }
    
    ll ans = 1;
    for (ll j = 1; j < n; j++) {
        if (nums[j] > nums[j + 1]) {
            ans++;
        }
    }

    for (ll j = 0; j < oper; j++)
    {
        ll a, b;
        cin >> a >> b;
        
        //cout << check(nums, ins, a, n) << endl;
        ans -= check(nums, ins, a, n);
        ans -= check(nums, ins, b, n);

        
        
        
        ll temp = nums[ins[a]];
        nums[ins[a]] = nums[ins[b]];
        nums[ins[b]] = temp;


        ans += check(nums, ins, a, n);
        ans += check(nums, ins, b, n);
        

        cout << ans << endl;
    }

    
}