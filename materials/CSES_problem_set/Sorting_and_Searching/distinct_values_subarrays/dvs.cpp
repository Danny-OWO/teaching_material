#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n; cin >> n;
    long long ins = 0;
    long long count = 0;
    long long ans = 0;

    map<long long ,long long > m;
    while (1)
    {
        if (ins == n)
        {
            ans += (count * (count+1))/2;
            break;
        }

        long long x; cin >> x; ins++;
        auto p = m.find(x);
        if (p == m.end())
        {
            m[x] = ins;
            count++;
        }
        else
        {
            ans += (count * (count+1))/2;
            count = ins - m[x];
            long long temp = count-1;
            ans -= (temp * (temp+1))/2;
            
            m[x] = ins;
            
        }
        
    }
    cout << ans << endl;
}