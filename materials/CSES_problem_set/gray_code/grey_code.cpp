#include <iostream>
#include <vector>
using namespace std;

vector<string> generator( vector<string> ans, long long remain)
{
    remain -= 1;
    if (remain == 0)
    {
        return ans;
    }
    for (long long i = ans.size()-1; i >= 0 ; i--)
    {
        ans.push_back(ans[i]);
    }
    for (long long i = 0; i < ans.size()/2 ; i++)
    {
        ans[i] += "0";
    } 
    for (long long i = ans.size()/2; i < ans.size() ; i++)
    {
        ans[i] += "1";
    } 
    return generator(ans,remain);

}





int main()
{
    long long x;
    cin >> x;
    vector<string> ans= {"0","1"};
    ans = generator(ans, x);


    for (long long i = 0; i < ans.size(); i++)
    {
        string target = ans[i];
        for (long long j = target.size()-1; j >= 0 ; j--)
        {
            cout << target[j];
        }
        cout << "" << endl;
    }
}