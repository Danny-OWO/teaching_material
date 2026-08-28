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


    move(n-1, from, end, middle); //先把最大的上面一個個移開 先移到 middle 所以 middle 當作 end

    cout << from << " " << end << endl; // 負責輸出 以及 最大的移到end的輸出

    move(n-1,middle,from,end); // 把上面的從 middle 移回 end
    
    return 0;
}



int main()
{
    int n;
    cin >> n;
    cout << pow(2,n)-1 << endl;
    move(n, 1,2,3);
}
