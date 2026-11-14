#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using vvi = vector<vector<int>>;
using vi = vector<int>;
ll ans = 0;

int board[8][8] = {};
int col[8] = {};
int r_c_ft[15] = {};
int s_r_c_ft[15] = {};


void dfs(int row_now)
{
    if (row_now == 8)
    {
        ans += 1;
        return;
    }

    for (int cc = 0; cc < 8 ; cc++)
    {
        if (board[cc][row_now] != 1)
        {
            if (col[cc] != 1)
            {
                if (r_c_ft[row_now-cc+7] != 1)
                {
                    if (s_r_c_ft[14-row_now-cc] != 1)
                    {
                        col[cc] = 1;
                        r_c_ft[row_now-cc+7] = 1;
                        s_r_c_ft[14-row_now-cc] = 1;
                        dfs(row_now+1);
                        col[cc] = 0;
                        r_c_ft[row_now-cc+7] = 0;
                        s_r_c_ft[14-row_now-cc] = 0;
                    }
                }
            }
        }
    }
}








int main()
{
    for (int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            char x;
            cin >> x;

            if (x == '*')
            {
                board[j][i] = 1;
            }
        }
    }

    dfs(0);

    cout << ans << endl;
}
