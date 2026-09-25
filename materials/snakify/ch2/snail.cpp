#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    float ee = b-c;
    float xd = a-b;
    cout << ceil(xd/ee)+1 << endl;
}