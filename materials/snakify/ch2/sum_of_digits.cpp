#include <iostream>
using namespace std;
int main()
{
    int x;
    cin >> x;
    int a = x % 10;
    int b = (x-a)/10%10;
    int c = (x-a-b*10)/100;

    cout << a+b+c << endl;
}