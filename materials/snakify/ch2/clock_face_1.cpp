#include <iostream>
using namespace std;
int main()
{
    float h, m, s;
    cin >> h >> m >> s;
    float xxx = h+m/60+s/3600;
    cout << xxx*30 << endl;
}