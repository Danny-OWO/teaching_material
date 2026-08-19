#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    string x;
    stack<ll> s1;
    stack<ll> s2;

    while (cin >> x)
    {
        ll y;

        if (x == "push")
        {
            cin >> y;

            s1.push(y);
            cout << 1;
        }
        else if (x == "pop")
        {
            if (s2.empty())
            {
                while (!s1.empty())
                {
                    s2.push(s1.top());
                    s1.pop();

                    cout << 5;
                }
            }

            s2.pop();
            cout << 4;
        }
    }
}