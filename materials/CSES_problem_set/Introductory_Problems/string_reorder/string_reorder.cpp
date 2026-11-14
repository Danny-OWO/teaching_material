#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll lst[26] = {0};
string y = "";

void proceed()
{
    ll n = -1;
    ll m = -1;

    for (int i = 0; i < 26; i++)
    {
        if (lst[i] > 0)
        {
            n = i;
        
            for (int j = i+1; j < 26; j++)
            {
                if (lst[j] > 0)
                {
                    m = j;
                    break;
                }
            }
        }
    }
    

    if (m == -1 && n != -1 && lst[n] == 1)
    {
        if (int(y[y.size()-1])-65 == n)
        {
            if (int(y[0])-65 == n)
            {
                cout << -1 << endl;
                return;
            }
            else
            {
                y = char(n+65) + y;
                cout << y << endl;
                return;
            }
        }
        else
        {
            y += char(n+65);
            cout << y << endl;
            return;
        }
    }
    else
    {
        lst[n] -= 1;
        lst[m] -= 1;
        y += char(n+65);
        y += char(m+65);
        proceed();
        return;
    }
    return;


}





int main()
{
    string x;
    cin >> x;


    for (ll i = 0 ; i < x.size(); i++)
    {
        lst[int(x[i])-65] += 1; 
    }

    
    proceed();
    




    // cout << int('A') << int('Z') << endl;

}
