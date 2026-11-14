#include <iostream>
using namespace std;
int main()
{
    long long n;
    cin >> n;
    for (long long i=0; i <n;i++)
    {
        long long y,x;
        cin >> y;
        cin >> x;
        long long key=y;

        if (x>y)
        {
            key = x;
        }
        

        if (key % 2 == 1)
        {
            if (x>y)
            {
                long long k =x;
                long long u =y;
                cout << k*k-u+1 <<endl;
            }
            else
            {
                long long k =y;
                long long u =x;
                cout << k*k+u+1-2*k <<endl;
            }
        }
        else
        {
            if (y>x)
            {
                long long k =y;
                long long u =x;
                cout << k*k-u+1 <<endl;
            }
            else
            {
                long long k =x;
                long long u =y;
                cout << k*k+u+1-2*k <<endl;
            }
        }


    




        
    }
}