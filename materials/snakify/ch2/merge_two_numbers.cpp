#include <iostream>
using namespace std;
int main()
{
    int x,y;
    cin >> x >> y;
    int a = x%10;
    int b = (x-a)/10;
    int c = y % 10;
    int d = (y-c)/10;
    cout << b*1000+d*100+a*10+c << endl;
}