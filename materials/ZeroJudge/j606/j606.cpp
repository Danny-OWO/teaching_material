#include <bits/stdc++.h>
using namespace std;
int main()
{
    int k, q, r;
    cin >> k >> q >> r;
    char word[100];
    char ans[100][100];
    scanf("%s", word);
    for (int i = 0; i < q; i++)
    {
        char temp[21];
        for (int j = 0; j < k; j++)
        {
            int y; cin >> y;
            temp[y-1] = word[j];
        }
        strcpy(ans[i], temp);
        strcpy(word, temp);
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < q; j++)
        {
            cout << ans[j][i];
        }
        cout << '\n';
    }
}