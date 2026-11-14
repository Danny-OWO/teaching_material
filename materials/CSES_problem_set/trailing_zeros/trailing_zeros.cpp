#include <iostream>
using namespace std;

long long countt(long long i)
    {
        if (i % 5 == 0)
        {
            return 1 + countt(i / 5);
        }
        else
        {
            return 0;
        }
    }



int main()
{
    




    long long z;
    cin >> z;
    long long det = 0;
    for (long long i = 5; i <= z; i += 5)
    {
        det += countt(i);
    }
    cout << det<< endl;
}