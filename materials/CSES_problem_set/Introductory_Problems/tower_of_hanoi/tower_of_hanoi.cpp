#include <iostream>
#include <cmath>
using namespace std;

/*
 move(n, from, aux, to)

 1. move(n-1, from, to, aux)

 2. from -> to

 3. move(n-1, aux, from, to)
 */

int move(int n, int from, int middle, int end)
{
    if (!n)
    {
        return 0;
    }
    move(n-1,from,end,middle);
    cout << from << " " << end << endl;
    move(n-1,middle,from,end);
    return 0;
}



int main()
{
    int n;
    cin >> n;
    cout << pow(2,n)-1 << endl;
    move(n, 1,2,3);
}
