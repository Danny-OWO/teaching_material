# CSES 題目方法總整理

這份筆記依照目前 repository 中的程式碼整理。相同題目的 `_1`、`_2`、`by_gemini` 等版本合併在同一列；「狀態」描述的是目前檔案，而不是題目本身。

## 方法索引

- **DFS／回溯**：Apple Division、Chessboard and Queens、Grid Paths
- **遞迴／分治式建構**：Tower of Hanoi、Gray Code、Digital Queries（目前寫法）
- **排序 + greedy**：Apartments、Ferris Wheel、Movie Festival、Missing Coin Sum
- **雙指標**：Apartments、Ferris Wheel
- **Sliding window**：Playlist
- **位置陣列／局部更新**：Collecting Numbers、Collecting Numbers II
- **平衡樹（set / multiset）**：Traffic Lights、Towers（以二分搜尋維護）
- **Kadane**：Maximum Subarray Sum
- **數學／公式**：Bit Strings、Coin Piles、Missing Number、Number Spiral、Trailing Zeros、Two Knights
- **計數／字串建構**：Creating Strings、Palindrome Reorder、String Reorder

## Introductory Problems

| 題目 | 核心方法 | 關鍵想法 | 時間複雜度 | 狀態／提醒 |
|---|---|---|---|---|
| Weird Algorithm | 直接模擬 | 按 Collatz 規則一路更新到 1 | 與序列長度成正比 | 已實作 |
| Missing Number | 數學、總和差 | 用 `n(n+1)/2` 減掉輸入值 | `O(n)` | 已實作；注意乘法使用 `long long` |
| Repetitions | 線性掃描、run length | 維護目前連續長度與最大值 | `O(n)` | 方法正確；`holder` 未初始化、以 `x[n] == '\0'` 判斷結尾不夠安全，宜改 range loop 或 `n < x.size()` |
| Increasing Array | Greedy、線性掃描 | 若當前值小於前一個合法值，就補到一樣高 | `O(n)` | 已實作 |
| Permutations | 建構法 | 分開輸出奇數與偶數，避免相鄰差為 1 | `O(n)` | 已實作 |
| Number Spiral | 數學、分段討論 | 由 `max(x,y)` 所在平方層與奇偶方向直接算答案 | 每筆 `O(1)` | 已實作 |
| Two Knights | 組合計數、補集 | 全部放法 `C(k²,2)` 減掉會互攻的 `4(k-1)(k-2)` | 每個棋盤 `O(1)`，總計 `O(n)` | 已實作；程式中的展開公式與標準式等價 |
| Two Sets | 數學判定、constructive algorithm | 總和須為偶數，即 `n mod 4` 為 0 或 3，再成對分組 | `O(n log n)`（目前另有排序） | 已實作；建構本身可做到 `O(n)` |
| Bit Strings | 模運算 | 重複乘 2 並對 `1e9+7` 取模 | `O(n)` | 可用 binary exponentiation 改為 `O(log n)`，但本題 `O(n)` 通常足夠 |
| Trailing Zeros | 質因數計數 | 計算 `n!` 中因數 5 的總個數 | 目前約 `O(n log_5 n / 5)` | 結果想法正確；標準寫法直接加 `n/5 + n/25 + ...`，為 `O(log n)` |
| Coin Piles | 數學必要充分條件 | 需滿足 `(a+b)%3==0` 且較大堆不超過較小堆兩倍 | 每筆 `O(1)` | 已實作 |
| Palindrome Reorder | 字元頻率、constructive algorithm | 偶數長不得有奇數頻率；奇數長恰有一種奇數頻率 | `O(n + alphabet)` | 已實作 |
| Gray Code | 反射建構、遞迴 | 複製目前序列並反轉其中一半，再補 0/1 | `O(n2^n)`（輸出量級） | 已實作；也可直接用 `i ^ (i >> 1)` |
| Tower of Hanoi | 遞迴 | 搬 `n-1`、搬最大盤、再搬 `n-1` | `O(2^n)` | 已實作；步數建議用位移或整數運算，避免 `pow` 的浮點型別 |
| Creating Strings | 排序、排列生成 | 排序後反覆呼叫 `next_permutation`，自然去除重複排列 | `O(P·n)`，`P` 為不同排列數 | 已實作；排列數用多項式係數 `n! / ∏c_i!` |
| Apple Division | DFS、子集合枚舉、回溯 | 每個重量選或不選，最小化兩組差 | `O(2^n)` | 已實作；這是典型 binary decision tree |
| Chessboard and Queens | DFS、回溯、剪枝 | 每列放一后，以欄及兩條對角線陣列做 `O(1)` 衝突檢查 | 最壞約 `O(8!)` | 已實作 |
| Grid Paths | DFS、回溯、剪枝 | 依指令走訪未使用格；遇到路徑把未走區域切斷時提早停止 | 指數級，剪枝後可過 | `gpd_2.cpp` 是主要版本；其他早期版本有型別／回溯／過早 `return` 問題 |
| Digit Queries | 數位區塊定位 | 先跳過 1 位數、2 位數……區塊，再算目標整數及其位數 | 每筆 `O(log k)` | `digital_queries_1.cpp` 方法清楚；以遞迴實作，但本質不是 DFS |
| String Reorder | 頻率計數、Greedy 建構 | 每步避免選到前一字元，且必須優先處理即將超過剩餘容量一半的字元 | `O(26n)` | `string_reorder_1.cpp` 為較合理版本；應再用測資驗證完整正確性 |
| Raab Game I | 數學判定、constructive algorithm | 依要求的勝／敗／平局數旋轉部分排列來構造兩組答案 | `O(n)` 每筆 | 已有建構版本；邊界條件較多，建議補 exhaustive 小測資驗證 |

## Sorting and Searching

| 題目 | 核心方法 | 關鍵想法 | 時間複雜度 | 狀態／提醒 |
|---|---|---|---|---|
| Distinct Numbers | 排序、線性計數 | 排序後計算相鄰不同值 | `O(n log n)` | 目前以 `holder = 0` 當哨兵；若輸入可能含 0 會漏算，宜用 `i==0` 或 `set` |
| Apartments | 排序、雙指標、Greedy | 比較目前申請者與公寓；太小移公寓，太大移申請者，符合則兩者都移 | `O(n log n + m log m)` | 已實作 |
| Ferris Wheel | 排序、雙指標、Greedy | 最重者必須搭一台；若能配最輕者就一起搭 | `O(n log n)` | `fw_1.cpp` 是標準且較穩定版本 |
| Concert Tickets | multiset、upper_bound | 對每位顧客找第一張「大於預算」的票，再退一格並刪除 | `O((n+m) log n)` | **未完成**；`ct.cpp` 停在空的 `for ()` |
| Movie Festival | 結束時間排序、Greedy | 永遠選目前能看的電影中最早結束者 | `O(n log n)` | 已實作；經典 interval scheduling |
| Maximum Subarray Sum | Kadane's algorithm（DP） | `bestEndingHere = max(a[i], bestEndingHere+a[i])` | `O(n)` | `mss_1.cpp` 是正確標準版；`mss.cpp` 的 prefix-sum 寫法不完整 |
| Stick Lengths | 中位數、排序 | 絕對差總和在中位數處最小 | `O(n log n)` | 已實作 |
| Missing Coin Sum | 排序、Greedy、不變量 | 若目前能組出 `[1, cur]` 且下一枚 `x <= cur+1`，範圍擴成 `[1, cur+x]` | `O(n log n)` | 已實作 |
| Collecting Numbers | 位置陣列、逆序斷點 | 建 `pos[value]`；若 `pos[x] > pos[x+1]` 就需多一輪 | `O(n)` | `cn_1.cpp` / `cn_by_gemini.cpp` 正確；`cn.cpp` 是把相鄰位置誤當相鄰數值 |
| Collecting Numbers II | 位置陣列、局部更新 | 交換只會影響被交換值附近的 `(v-1,v)`、`(v,v+1)` 斷點 | 初始化 `O(n)`，每次查詢 `O(1)`（只檢查常數組關係） | `cnt_by_gemini.cpp` 是最完整版本；早期版本有索引和值混淆及邊界問題 |
| Playlist | Sliding window、last occurrence map | 右界前進；重複時左界跳到該值上次位置的下一格，且不可倒退 | `O(n log n)`（`map`） | `p_by_gemini.cpp` 正確；`p.cpp` 少了 `l = max(l, last+1)` 的保護 |
| Towers | Greedy、二分搜尋 | 維護每座塔頂；對方塊 `x` 找第一個 `>x` 的塔頂替換，否則新建塔 | `O(n log n)` | 已實作；概念近似 patience sorting |
| Traffic Lights | ordered set + multiset | `set` 找新燈左右鄰居；從 `multiset` 刪舊區間並加入兩個新區間 | `O(m log m)` | `tl_by_gemini.cpp` 是標準版；刪 multiset 單一元素要用 iterator |
| Distinct Values Subarrays | Sliding window、頻率表 | 維護最多 `k` 種值的視窗；每個右端點貢獻 `r-l+1` 個合法子陣列 | `O(n log n)` 或期望 `O(n)` | **尚未實作**；`dvs.cpp` 是空檔案 |

## 最值得記住的辨識訊號

1. **「選或不選、列舉所有可能」**：先想 DFS／回溯；若 `n` 約 20，`2^n` 常可接受。
2. **「排序後配對最大與最小」**：常是雙指標 + greedy，例如 Ferris Wheel。
3. **「最長且不能重複的連續區間」**：sliding window + 最後出現位置，例如 Playlist。
4. **「每次更新後只改少數關係」**：不要整份重算，找局部不變量，例如 Collecting Numbers II。
5. **「動態找前驅／後繼，還要插入刪除」**：`set` / `multiset`，例如 Traffic Lights、Concert Tickets。
6. **「最大連續和」**：直接想到 Kadane；狀態是「以目前位置結尾的最佳答案」。
7. **「最小化絕對差總和」**：中位數；「最小化平方差」才是平均數。兩者別混。

## 建議修題順序

1. 先補完 **Concert Tickets**、**Distinct Values Subarrays**。
2. 修正 **Distinct Numbers** 的哨兵值與 **Repetitions** 的未初始化／越界風險。
3. 只保留或標記每題的正確主版本：`mss_1.cpp`、`cn_1.cpp`、`p_by_gemini.cpp`、`tl_by_gemini.cpp`、`cnt_by_gemini.cpp`、`gpd_2.cpp`。
4. 對 **String Reorder**、**Raab Game I** 做小範圍 exhaustive testing；constructive 題最會用「看起來很合理」的方式背刺你。
