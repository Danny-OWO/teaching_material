#include <bits/stdc++.h>
using namespace std;
int main()
{
    string x;
    cin >> x;
    string y;
    cin >> y;
    vector<int> nums(26);
    for (int i = 0; i < y.size(); i++)
    {
        char tar = y[i];
        nums[y[i] - 'A']++;
    }

    vector<int> prefix;
    prefix.push_back(0);
    int temp = 0;
    for (int j = 0; j < x.size(); j++)
    {

    }



}