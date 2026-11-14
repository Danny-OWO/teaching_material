#include <iostream>
using namespace std;
int main()
{
    long long x;
    cin >> x;
    long long exp = x * (x+1) /2;
    for (long long n = 0; n < x-1; n++)
    {
        long long k;
        cin >> k;
        exp -= k;
    }
    cout << exp << endl;
}