#include <iostream>
using namespace std;
int main()
{
    int a;
    cin >> a;
    int b = (a-a%100)/100;
    int c = a % 100;

    cout << c*100+b << endl;
}