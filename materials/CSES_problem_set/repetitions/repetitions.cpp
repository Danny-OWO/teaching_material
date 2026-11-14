#include <iostream>
using namespace std;
int main()
{
    string x;
    cin >> x;
    long long n = 0;

    char holder;
    long long last = 0;
    long long biggest = 0;
    while (1)
    {
        if (x[n] == '\0')
        {
            break;
        }

        char cur = x[n];
        if (cur != holder)
        {
            last = 1;
            holder = cur;
        }
        else
        {
            last +=1;
        }

        if (last > biggest)
        {
            biggest = last;
        }

        n+=1;

    }
    cout << biggest << endl;
}