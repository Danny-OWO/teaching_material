#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string x;
    cin >> x;
    vector<long long> times(26,0);
    long long size = x.size();
    for (long long i=0; i < size; i++)
    {
        times[x[i]-65]+=1;
    }

    string ans="";
    if (size % 2 ==0)
    {
        for (int i =0; i < 26; i++)
        {
            if (times.at(i) % 2 != 0)
            {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
            else
            {
                for (long long k=0; k < times.at(i)/2; k++)
                {
                    ans += char(i+65);
                }
                
            }
        }
        cout << ans;
        for (long long u=ans.size()-1; u >= 0; u--)
        {
            cout << ans[u];
        }
    }
    else
    {
        int oddtimes = 0;
        int oddindex = -1;
        for (int i=0;i<26;i++)
        {
            if (times.at(i) % 2 != 0)
            {
                oddtimes+=1;
                oddindex = i;
            }
            else
            {
                for (long long k=0; k < times.at(i)/2; k++)
                {
                    ans += char(i+65);
                }
            }
        }
        if (oddtimes != 1)
        {
            cout << "NO SOLUTION" << endl;
            return 0;
        }
        else
        {
            cout << ans;
            for (long long u = 0; u < times.at(oddindex); u++)
            {
                cout << char(oddindex+65);
            }
            for (long long u=ans.size()-1; u >= 0; u--)
            {
            cout << ans[u];
            }            
        }



    }

}