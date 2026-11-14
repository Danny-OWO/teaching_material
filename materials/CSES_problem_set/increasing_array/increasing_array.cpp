#include <iostream>
using namespace std;
int main()
{
    long long x;
    cin >> x;
    long long cost = 0;

    long long former;
    cin >> former;


    for (int n = 1; n < x; n++)
    {
        long long cur;
        cin >> cur;
        if (cur < former)
        {
            cost += former - cur;
        }
        else
        {
            former = cur;
        }
    }
    cout << cost << endl;
}