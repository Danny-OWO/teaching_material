#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {

    ll x;
    if (!(cin >> x)) return 0;

    vector<ll> song(x);
    for (ll i = 0; i < x; i++) {
        cin >> song[i];
    }

    // 使用 unordered_map 效能通常比 map 更好 (O(1) vs O(log N))
    // 儲存格式 -> songmap[歌曲ID] = 該歌最後出現的 (Index + 1)
    map<ll, ll> songmap;
    
    ll l = 0;
    ll mmm = 0;

    for (ll r = 0; r < x; r++) {
        ll the_song = song[r];

        // 如果這首歌出現過，且它的前一次位置在當前視窗 [l, r] 內
        // 左邊界 l 必須跳到該重覆歌曲「下一個位置」
        if (songmap.count(the_song)) {
            l = max(l, songmap[the_song]);
        }

        // 更新當前這首歌的新位置（儲存 r + 1，方便下次發生重覆時，l 直接跳到它的下一格）
        songmap[the_song] = r + 1;

        // 計算目前合法視窗長度並取最大值
        mmm = max(mmm, r - l + 1);
    }

    cout << mmm << "\n";
    return 0;
}