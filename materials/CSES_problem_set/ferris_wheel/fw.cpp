#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
ll ans = 0;
int main()
{
    ll n, x;
    cin >> n >> x;
    vector<ll> childsthin;
    vector<ll> childsfat;
    for (ll i = 0; i < n; i++)
    {
        ll k;
        cin >> k;
        if (k > x / 2)
        {
            childsfat.pb(k);
        }
        else
        {
            childsthin.pb(k);
        }
    }

    sort(childsfat.begin(),childsfat.end(), greater<ll>());
    //cout << childsfat[0] << endl;
    sort(childsthin.begin(),childsthin.end());
    
    ll i = 0;
    ll j = 0;
    while (i < childsfat.size())
    {
        ll tar = childsfat[i];
        ll acc = childsthin[j];
        //cout << tar << "+++++++++" << acc << endl;
        if (tar + acc <= x)
        {
            i++;
            j++;
            ans++;
        }
        else
        {
            i++;
            ans++;
        }
    }

    j = childsthin.size() - j;
    //cout << ans << endl;
    //cout << j << endl;
    cout << ans + j % 2 + j / 2 << endl;

    


}