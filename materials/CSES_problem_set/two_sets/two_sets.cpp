#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    long long n;
    cin >> n;

    if (n % 4 == 1 || n % 4 == 2)
    {
        cout << "NO" << endl;
    }
    else if (n % 4 == 3)
    {
        cout << "YES" << endl;
        vector<long long> x;
        vector<long long> y;
        long long combos = (n/2+1)/2;
        for (long long i = 1; i <= combos; i++)
        {
            x.push_back(i);
            x.push_back(n-i);
        }
        for (long long i = combos+1; i <= combos + (((n/2)-1)/2) ; i++)
        {
            y.push_back(i);
            y.push_back(n-i);
        }
        y.push_back(n);


        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        cout << n / 2 +1 << endl;

        for (long long i = 0; i < x.size(); i++)
        {
            cout << x.at(i) << " ";
        }
        cout << "" << endl;
        cout << n / 2  << endl;
        for (long long i = 0; i < y.size(); i++)
        {
            cout << y.at(i) << " ";
        }
    }
    else
    {
        cout << "YES" << endl;
        vector<long long> x;
        vector<long long> y;
        long long combos = (n/2)/2;
        for (long long i = 1; i <= combos; i++)
        {
            x.push_back(i);
            x.push_back(n-i+1);
        }
        for (long long i = combos+1; i <= n / 2 ; i++)
        {
            y.push_back(i);
            y.push_back(n-i+1);
        }



        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        cout << n / 2  << endl;

        for (long long i = 0; i < x.size(); i++)
        {
            cout << x.at(i) << " ";
        }
        cout << "" << endl;
        cout << n / 2  << endl;
        for (long long i = 0; i < y.size(); i++)
        {
            cout << y.at(i) << " ";
        }
    }

}