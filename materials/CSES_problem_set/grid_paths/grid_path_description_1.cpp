#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string k;
bool check[7][7] = {0};
ll ans = 0;


bool test(ll x, ll y)
{
    bool e = x < 0 || x > 6;
    bool g = y < 0 || y > 6;
    if (e || g)
    {

        return false;
    }
    else if (!check[x][y])
    {
        check[x][y] = true;
        return true;
    }
    return false;
}





void dfs(ll step, ll x, ll y)
{
    //test
    cout << step << " " << x << " " << y << '\n';
    //test
    if (step == 48)
    {
        if (x == 0 && y == 6)
        {
            ans += 1;
            return;
        }
        return;
    }
    else
    {
        if (x == 0 && y == 6)
        {
            return;
        }
    }

    char order = k[step];

    if (order != '?')
    {
        if (order == 'L')
        {
            bool result = test(x-1,y);
            if (result)
            {
                dfs(step+1, x-1, y);
                check[x-1][y] = false;
                return;
            }
            return;
        }

        if (order == 'R')
        {
            bool result = test(x+1,y);
            if (result)
            {
                dfs(step+1, x+1, y);
                check[x+1][y] = false;
                return;
            }
            return;
        }

        if (order == 'D')
        {
            bool result = test(x,y+1);
            if (result)
            {
                dfs(step+1, x, y+1);
                check[x][y+1] = false;
                return;
            }
            return;
        }

        if (order == 'U')
        {
            bool result = test(x,y-1);
            if (result)
            {
                dfs(step+1, x, y-1);
                check[x][y-1] = false;
                return;
            }
            return;
        }
    }


    if (order == '?')
    {
        bool result = test(x-1,y);
        if (result)
        {
            dfs(step+1, x-1, y);
            check[x-1][y] = false;
        }
    

        result = test(x+1,y);
        if (result)
        {
            dfs(step+1, x+1, y);
            check[x+1][y] = false;
        }



        result = test(x,y+1);
        if (result)
        {
            dfs(step+1, x, y+1);
            check[x][y+1] = false;
        }


        result = test(x,y-1);
        if (result)
        {
            dfs(step+1, x, y-1);
            check[x][y-1] = false;
        } 
    }
    return;

}






int main()
{
    cin >> k;
    check[0][0] = true;
    dfs(0,0,0);

    cout << ans << endl;
}