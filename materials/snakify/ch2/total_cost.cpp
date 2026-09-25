#include <iostream>
using namespace std;
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    b += a*100;
    b *= c;
    cout << b/100 << ' ' << b %100 << endl;
}