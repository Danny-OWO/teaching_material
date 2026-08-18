#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void check()
{
    string word; cin >> word;
    stack<ll> s;
    for (ll j = 0; j < word.size(); j++)
    {
        char cur = word[j];
        ll tag = 0;
        switch (cur)
        {
            case '(':
                tag += 1;
                break;
            case '[':
                tag += 2;
                break;
            case '{':
                tag += 3;
                break;
            case '<':
                tag += 4;
                break;
            case ')':
                tag -= 1;
                break;
            case ']':
                tag -= 2;
                break;
            case '}':
                tag -= 3;
                break;
            case '>':
                tag -= 4;
                break;

        }

        if (tag > 0)
        {
            s.push(tag);
        }
        else
        {
            if (s.empty())
            {
                cout << 'N' << endl;
                return;
            }
            else
            {
                if (s.top() + tag == 0)
                {
                    s.pop();
                }
                else
                {
                    cout << 'N' << endl;
                    return;
                }
            }
        }
    }

    if (s.empty())
    {
        cout << 'Y' << endl;
        return;
    }
    else
    {
        cout << 'N' << endl;
        return;
    }
}








int main()
{
    ll n; cin >> n;
    for (ll i = 0; i < n; i++)
    {
        check();
    }
}