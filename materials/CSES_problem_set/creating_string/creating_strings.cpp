#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;
int creating_strings()
{
    vector<char> words = {};
    string container;
    unordered_map<char,int> mp;
    cin >> container;
    long long amount = 1;
    for (int i = 0; i < container.size(); i++)
    {
        char tar = container[i];
        if (mp.find(tar) != mp.end())
        {
            mp[tar] += 1;
        }
        else
        {
            mp[tar] = 1;
        }

        amount *= (i+1);
    }

    for (auto &p : mp)
    {
        for (int j = 1; j <= p.second; j++)
        {
            amount /= j;
        }

    }


    cout << amount << endl;


    sort(container.begin(), container.end());

    cout << container << endl;
    while (next_permutation(container.begin(), container.end())) {
        cout << container << "\n";
    }






    return 0;
}
int main() {
    creating_strings();
}
