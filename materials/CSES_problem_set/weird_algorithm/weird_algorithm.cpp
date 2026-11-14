#include <iostream>
using namespace std;

int main()
{
    
    long long x;
    cin >> x;

    cout << x << " ";



    while (1)
    {
        if (x == 1)
        {
            return 0;
        }
        
        if (x % 2 == 1)
        {
            x = 3*x+1;
            cout << x << " ";
        }
        else
        {
            x = x / 2;
            cout << x << " ";
        }
    }

}