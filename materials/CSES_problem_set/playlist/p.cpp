#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back

int main()
{
    ll x;
    cin >> x;
    vector<ll> song;
    map<ll,ll> songmap;



    for (ll i = 0; i < x; i++)
    {
        ll o; cin >> o;
        song.pb(o);
    }


    if (x == 1)
    {
        cout << 1 << endl;
        return 1;
    }




    ll l = 0;
    ll r;
    ll mmm = 0;
    songmap[song[l]] = l+1;

    for (ll j = 1; j < x; j++)
    {
        ll the_song = song[j];
        if (j == 1)
        {
            r = 1;
        }
        else
        {
            r++;
        }
        if (songmap[the_song] != 0)
        {
            l = songmap[the_song];
            songmap[the_song] = l + 1;
        }
        songmap[the_song] = r + 1;

        if (r - l + 1 > mmm)
        {
            mmm = r - l + 1;
        }
    }

    cout << mmm << endl;
}