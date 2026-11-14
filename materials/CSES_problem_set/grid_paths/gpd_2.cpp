#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string k;
bool check[9][9] = {};
ll ans = 0;

bool cut(ll x, ll y)
{
    if (check[x][y+1] == true && check[x][y-1] == true && check[x+1][y] == false && check[x-1][y] == false)
    {
        return true;
    }
    else if (check[x+1][y] == true && check[x-1][y] == true && check[x][y+1] == false && check[x][y-1] == false)
    {
        return true;
    }
    return false;
}

void dfs(ll step, ll x, ll y)
{

    //cout<<step<<" "<<x<<" "<<y<<endl;
    if (step == 48)
    {
        if (x == 1 && y == 7)
        {
            ans += 1;
            return;
        }
        return;
    }
    if (x == 1 && y == 7)
    {
        return;
    }
    
    
    check[x][y] = true;


    

    
    
    char order = k[step];



    if (order == 'R')
    {

        if (check[x+1][y] != true && cut(x+1, y) != true)
        {
            dfs(step + 1, x + 1, y);
            //check[x+1][y] = false;
            //return;
        }

    }

    else if (order == 'L')
    {

        if (check[x-1][y] != true && cut(x-1, y) != true)
        {
            dfs(step + 1, x - 1, y);
            //check[x-1][y] = false;
            //return;
        }

    }

    else if (order == 'D')
    {

        if (check[x][y+1] != true && cut(x, y+1) != true)
        {
            dfs(step + 1, x, y + 1);
            //check[x][y+1] = false;
            //return;
        }

    }

    else if (order == 'U')
    {
        
        if (check[x][y-1] != true && cut(x, y-1) != true)
        {
            dfs(step + 1, x , y-1);
            //check[x][y-1] = false;
            //return;
        }

    }

    else
    {
       

        if (check[x+1][y] != true && cut(x+1, y) != true)
        {
            dfs(step + 1, x + 1, y);
            //check[x+1][y] = false;
        }

        if (check[x-1][y] != true && cut(x-1, y) != true)
        {
            dfs(step + 1, x - 1, y);
            //check[x-1][y] = false;
        }



        
        if (check[x][y+1] != true && cut(x, y+1) != true)
        {
            dfs(step + 1, x, y + 1);
            //check[x][y+1] = false;
        }

        if (check[x][y-1] != true && cut(x, y-1) != true)
        {
            dfs(step + 1, x , y-1);
            //check[x][y-1] = false;
        }

    }
    check[x][y] = false;
    return;
}



int main()
{
    for (int i = 0; i < 9; i++)
    {
        check[i][0] = true;
        check[0][i] = true;
        check[8][i] = true;
        check[i][8] = true;
    }

    cin >> k;
    dfs(0, 1, 1);
    cout << ans << endl;
    


}