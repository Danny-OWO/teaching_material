#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void test()
{
    ll n,a,b;
    cin >> n >> a >> b;
    ll t = n-a-b;

    if (a+b > n)
    {

        cout << "NO" << endl;
        return;
    }
    else if (t == n && a == 0 && b == 0)
    {
        cout << "YES" << endl;
        for (ll i = 1; i < n+1; i++)
        {
            cout << i << " ";
        }
        cout << "" << endl;
        for (ll i = 1; i < n+1; i++)
        {
            cout << i << " ";
        }
        cout << "" << endl;
        return;
    }
    else if (t == n && n == 1)
    {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << 1 << endl;
        return;
    }
    else if (a == n || b == n)
    {
        cout << "NO" << endl;
        return;
    }
    else if (n-t == a && b == 0)
    {
        cout << "NO" << endl;
        return;
    }
    else if (n-t == b && a == 0)
    {
        cout << "NO" << endl;
        return;
    }
    else if (t == n-1)
    {
        cout << "NO" << endl;
        return;
    }
    else
    {
        cout << "YES" << endl;
        n -= t;
        for (ll i = n-a+1; i < n+1; i++)
        {
            cout << i << " ";
        }
        for (ll i = 1; i < n-a+1; i++)
        {
            cout << i << " ";
        }
        for (ll i = n+1; i < n+1+t; i++)
        {
            cout << i << " ";
        }
        cout << "" << endl;
        for (ll i = 1; i < n+t+1; i++)
        {
            cout << i << " ";
        }
        cout << "" << endl;
        return;
    }



}







int main()
{
    ll n;
    cin >> n;
    for (ll i = 0 ; i < n; i++)
    {
        test();
    }
}
