#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    long long x;
    cin >> x;
    long long tar = 1;

    for (long long i = 0; i < x; i++)
    {
        tar = tar * 2 % 1000000007;
    }


    cout << tar << endl;




    // x+=1;
    // long long y = (x / 10) * 3 ;
    // long long d = x % 10;
    // if (d<=4)
    // {
    //     y +=1;
    // }
    // else if (d<=7)
    // {
    //     y+=2;
    // }
    // else
    // {
    //     y+=3;
    // }
    // vector<int> num;
    // for (long long i=1; i <= y; i++)
    // {
    //     long long div = 10;
    //     long long minus = tar%div;
    //     num.push_back(minus);
    //     tar -= minus;
    //     tar /= div;
    // }






    // for (long long i = num.size()-1; i >= 0 ; i--)
    // {
    //     cout << num.at(i);
    // }
    // cout << "" << endl;

}
