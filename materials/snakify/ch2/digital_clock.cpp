#include <iostream>
using namespace std;
int main()
{
    int a; 
    cin >> a;
    int b = a % 60;
    int c = a / 60;
    cout << c << ' ' << b << endl;
}