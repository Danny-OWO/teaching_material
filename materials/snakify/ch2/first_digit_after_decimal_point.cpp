#include <iostream>
using namespace std;
int main()
{
    float a;
    cin >> a;

    a *= 10;
    int b = (int) a;
    cout << b % 10 << endl;
}