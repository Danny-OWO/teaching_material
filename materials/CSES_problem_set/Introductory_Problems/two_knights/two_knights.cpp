#include <iostream>
using namespace std;
int main()
{
    long long n;
    cin >> n;
    for (long long i=1; i <n+1;i++)
    {
        cout << (i*i*i*i - i*i) / 2 - 4* i *i + 12*i-8<< endl;
    }
}