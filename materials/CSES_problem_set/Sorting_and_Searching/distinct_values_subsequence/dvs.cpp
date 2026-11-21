/*
This problem now need to use DP to solve

we define

total: so far how many valid subsequences
used[x]: so far how many valid subsequences that has contained 'x'

WYM?

so for example
here are three valid ones
A [1, 2, 3]
B [1, 3]
C [2, 4, 6, 7]

now we want to add a new one 'x' inside 
so every subsequence at first have their rights to deside whether getting x or not
well 
for the subsequences that already had x inside, they CANT get x 

for instance, we get a new x = 1
then subsequence A and B cannot insert x into their choice at all


so 

we define 
add = total - used[x]
and then total += add
and then used[x] += add
*/


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

int main()
{
    int n;
    cin >> n;
    map<ll,ll> used;
    ll total = 1;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        ll add = (total - used[x] + MOD) % MOD;

        total = (total + add) % MOD;
        used[x] = (used[x] + add) % MOD;
    }

    cout << (total - 1 + MOD) % MOD << endl;
}