#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    long long t;
    cin >> t;
    for(long long i=0; i <t; i++ )
    {
        long long a,b;
        cin >> a >> b;
        if (a == 0 && b == 0)
        {
            cout << "YES" << endl;
        }
        else if (a == 0 || b == 0)
        {
            cout << "NO" << endl;
        }
        else if ((a + b) % 3 != 0)
        {
            cout << "NO" << endl; 
        }
        else if (min(a,b) * 2 < max(a,b))
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
}