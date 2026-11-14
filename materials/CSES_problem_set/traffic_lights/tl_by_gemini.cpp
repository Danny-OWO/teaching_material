#include <iostream>
#include <set>

using namespace std;

int main() {


    ios_base::sync_with_stdio(false);
    cin.tie(NULL);



    int n, m;
    cin >> n >> m;

    set<int> lightloc = {0, n}; // 預先放進起點與終點
    multiset<int> length = {n}; // 初始長度為全全街長 n

    for (int i = 0; i < m; i++) {
        int nw;
        cin >> nw;

        // 1. 找到右邊第一個比 nw 大的路燈 R
        auto right_it = lightloc.upper_bound(nw);
        // 2. 左邊最近的路燈 L 就是 right_it 的前一個
        auto left_it = prev(right_it);

        int L = *left_it;
        int R = *right_it;

        // 3. 移除舊區間 (注意要傳入 iterator，只刪除一個元素)
        length.erase(length.find(R - L));

        // 4. 加入拆分後的兩個新區間
        length.insert(nw - L);
        length.insert(R - nw);

        // 5. 記錄新路燈位置
        lightloc.insert(nw);

        // 輸出當前最大的長度
        cout << *length.rbegin() << (i == m - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}