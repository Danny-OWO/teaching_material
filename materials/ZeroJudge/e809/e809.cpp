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
        temp += nums[x[j]-'A'];
        prefix.push_back(temp);
    }

    int n;
    cin >> n;

    for (int u = 0; u < n; u++)
    {
        int uu; cin >> uu;
        int index = lower_bound(prefix.begin(), prefix.end(), uu) - prefix.begin();
        //cout << index << endl;
        cout << x[index-1] << endl;
    }



}