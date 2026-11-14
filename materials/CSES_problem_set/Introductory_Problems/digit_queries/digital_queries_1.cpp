#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void ans(ll k, ll b, ll s, ll d)
{   
    if (k <= b * 9 * d)
    {
        ll number = s + (k-1)/d;
        cout << to_string(number)[(k-1)%d] << '\n';
    }
    else
    {

        s *= 10;
        k -= b * 9 * d;
        ans(k,b*10,s,d+1);
        return;
    }
    return;    
}







int main()
{
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++)
    {
        ll k;
        cin >> k;

        ans(k, 1, 1, 1);
    }
}