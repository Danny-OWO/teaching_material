#include <iostream>
using namespace std;
int main()
{
    long long x;
    cin >> x;
    if (x <= 3 && x != 1)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if (x == 4)
    {
        cout << "2 4 1 3" << endl;
    }
    else
    {
        for (long long n = 1; n <= x ; n+=2)
        {
            cout << n << " ";
        }
        for (long long n = 2; n <= x ; n+=2)
        {
            cout << n << " ";
        }
    }
}