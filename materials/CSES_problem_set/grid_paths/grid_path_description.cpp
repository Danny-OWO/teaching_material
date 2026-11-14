#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string k;
ll ans = 0;
bool check[7][7] = {0};
void dfs(ll step, ll x, ll y, bool check)
{
    
    char order = k[step];

    if (step == 48 && x == 0 && y == 6)
    {
        ans += 1;
        return;
    }

    if (order != '?')
    {
        if (order == 'L')
        {
            if (x > 0 && !check[x-1][y])
            {
                check[x-1][y] = true;
                dfs(step + 1 , x - 1, y, check);
                return;
            }
            else
            {
                return;
            }
        }
        else if (order == 'R')
        {
            if (x < 6 && !check[x+1][y])
            {
                check[x+1][y] = true;
                dfs(step + 1, x + 1, y, check);
                return;
            }
            else
            {
                return;
            }
        }
        else if (order == 'U')
        {
            if (y > 0 && !check[x][y-1])
            {
                check[x][y-1] = true;
                dfs(step + 1, x , y - 1, check);
                return;
            }
            else
            {
                return;
            }
        }
        else
        {
            if (y < 6 && !check[x][y+1])
            {
                check[x][y+1] = true;
                dfs(step + 1, x, y + 1, check);
                return;
            }
            else
            {
                return;
            }
        }
    }
    else
    {
        if (x > 0 && !check[x-1][y])
        {
            check[x-1][y] = true;
            dfs(step + 1, x - 1, y, check);
            return;
        }
        if (x < 6 && !check[x+1][y])
        {
            check[x+1][y] = true;
            dfs(step + 1, x + 1, y, check);
            return;
        }
        if (y > 0 && !check[x][y-1])
        {
            check[x][y-1] = true;
            dfs(step + 1, x , y - 1, check);
            return;
        }
        if (y < 6 && !check[x][y+1])
        {
            check[x][y+1] = true;
            dfs(step + 1, x , y + 1, check);
            return;
        }
        return;
    }
    return;
}




int main()
{
    
    cin >> k;
    check[0][0] == true;
    dfs(0 , 0 , 0, check);
}