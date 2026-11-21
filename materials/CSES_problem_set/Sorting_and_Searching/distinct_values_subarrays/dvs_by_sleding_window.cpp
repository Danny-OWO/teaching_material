#include <bits/stdc++.h>
using namespace std;


/*
假設現在的有效視窗是：
1 2 3 4
↑     ↑
L     R


所有以 right 結尾、且沒有重複元素的 subarray：
[4]
[3, 4]
[2, 3, 4]
[1, 2, 3, 4]


總共 4 個。

*/




int main()
{
    long long n;
    cin >> n;

    map<long long, long long> m;

    long long left = 1;
    long long ans = 0;

    for (long long right = 1; right <= n; right++)
    {
        long long x;
        cin >> x;

        if (m.find(x) != m.end())
        {
            left = max(left, m[x] + 1);
            /*
            但有一個陷阱！

            假設：
            位置:  1 2 3 4 5
            數字:  1 2 1 3 2


            當我們讀到最後一個 2：
            - left 已經是 3（因為之前第二個 1）。
            - m[2] 是 2。
            - 位置 2 的 2 已經在視窗外面。
            所以我們不能把 left 往回移動到 2。

            這就是為什麼需要：
            left = max(left, m[x] + 1);


            Sliding Window 的 left 永遠只能向右移動，不能往左退。
            
            
            
            
            
            */



        }

        m[x] = right;

        ans += right - left + 1;
    }

    cout << ans << '\n';
}