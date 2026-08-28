#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

ll f91(ll n)
{
    if (n <= 100)
    {
        return f91(f91(n+11));
    }
    else
    {
        return n-10;
    }
}




int main()
{
    ll n;
    cin >> n;
    while (n != 0)
    {
        cout << "f91(" << n << ") = "  << f91(n) << endl;

        cin >> n;
    }
}