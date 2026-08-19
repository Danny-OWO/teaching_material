# APCS / Competitive Programming Learning Route

> 這不是「把演算法名詞照順序看完」的清單，而是一條以 **APCS 實作穩定拿分**為主、再銜接競賽程式設計的訓練路線。

## 先校正方向

舊版內容大致沒有錯，但有四個結構性問題：

1. **太像 STL 功能表**：會 `priority_queue` 不等於會判斷何時該用它。
2. **複雜度出現太晚**：每一題都應先從限制估算可接受的時間複雜度。
3. **APCS 與資競混在一起**：BIT、Segment Tree、Tree DP 並非一般 APCS 準備的優先事項。
4. **缺少驗收標準**：看懂不算學會；能在限時內獨立 AC、解釋正確性與複雜度才算。

因此，本路線把內容分成「APCS 核心」與「競程延伸」，並把讀題、複雜度、測試與除錯貫穿所有階段。

---

## 每題固定工作流

1. 圈出輸入限制、輸出要求與特殊條件。
2. 先寫出最直接的暴力解，估算時間與空間複雜度。
3. 找出需要維護的狀態與不變量，再選資料結構或演算法。
4. 手算範例，另外自製最小、最大、重複、邊界與反例。
5. AC 後補寫：核心想法、正確性理由、複雜度、曾犯的錯。

一句難聽但有用的話：**不知道為什麼正確的模板，只是延後爆炸的炸彈。**

---

## A. APCS 核心路線

### 階段 0：C++ 生存能力與程式追蹤

**目標：** 能獨立完成單一流程題，並能逐行追蹤程式。

- 基本架構、`cin` / `cout`、變數、運算式、型別轉換
- `int`、`long long`、`double`、`char`、`bool`、`string`
- `if` / `else`、`for`、`while`、`break`、`continue`
- 函式、參數、回傳值、傳值與 reference
- 整數除法、餘數、位元運算的基本閱讀能力
- overflow、陣列越界、未初始化、無窮迴圈
- 用 debugger、手動 trace table 與最小反例除錯

**一定要提早學：** 根據資料範圍粗估 `O(1)`、`O(N)`、`O(N²)` 是否可行。

**驗收：** 30–40 分鐘內完成一題條件＋迴圈模擬；能說明迴圈執行次數。

**建議題目：**

- [q181. 等紅綠燈](https://zerojudge.tw/ShowProblem?problemid=q181)
- [q836. 小心陷阱](https://zerojudge.tw/ShowProblem?problemid=q836)

### 階段 1：序列、字串與精確模擬

**目標：** 能把題目敘述翻成狀態更新，不漏邊界。

- `vector`、一維／二維陣列、索引與遍歷
- `string`、字元與數字轉換、比較、切片觀念
- Grid 座標、方向陣列、邊界判斷
- 累計、最大最小、次數統計、狀態機式模擬
- `struct` / `pair` 表示一筆資料

先用陣列或排序解決統計問題；真正需要「動態查找」時再引入 `map` / `set` / `unordered_map`，不要見到計數就無腦上紅黑樹。

**驗收：** 能自己設計至少五組邊界測資；能分清「位置」、「值」與「目前狀態」。

**建議題目：**

- [q182. 字串操作](https://zerojudge.tw/ShowProblem?problemid=q182)
- [q837. 轉盤得分](https://zerojudge.tw/ShowProblem?problemid=q837)
- [r489. 航空拍照圖](https://zerojudge.tw/ShowProblem?problemid=r489)
- [r490. 商品包裝地](https://zerojudge.tw/ShowProblem?problemid=r490)

### 階段 2：排序、搜尋與 STL 基礎

**目標：** 看見「順序」與「查找」時，能選對工具並分析代價。

- `sort`、`stable_sort`、lambda comparator
- `pair` / `tuple` 的字典序與多條件排序
- 線性搜尋、手寫 binary search
- `lower_bound`、`upper_bound` 與半開區間 `[l, r)`
- `stack`、`queue`、`deque`、`priority_queue` 的語意與複雜度
- `set` / `map` 與 hash-based 容器的基本取捨

**驗收：** 給一段程式能說出 `O(N log N)` 從哪裡來；binary search 不靠複製模板也能處理不存在與重複值。

### 階段 3：前處理與區間技巧

**目標：** 將重複工作消掉，而不是讓電腦反覆做同一件事。

- 一維／二維前綴和
- 一維／二維差分
- two pointers 與 sliding window
- 座標壓縮的基本概念

注意：two pointers / sliding window 通常需要排序、非負數或某種單調性；條件不成立時硬套會得到一個跑很快的錯誤答案。

**驗收：** 能從限制判斷 `O(NQ)` 需要降成 `O(N+Q)` 或 `O((N+Q) log N)`，並解釋前處理保存了什麼資訊。

### 階段 4：遞迴、枚舉、DFS 與 Backtracking

**目標：** 能明確定義搜尋狀態、選擇與終止條件。

- base case、recursive case、call stack
- 子集合、排列、組合與 bitmask 枚舉
- Grid DFS、flood fill、connected components
- backtracking：選擇、遞迴、撤銷
- pruning 與搜尋樹大小估算

**驗收：** 能估算 `2^N`、`N!` 是否可行；不會把 visited 的標記／還原時機寫反。

### 階段 5：BFS 與圖論基礎

**目標：** 能把問題建模成圖，求無權最短路與連通性。

- vertex、edge、adjacency list
- DFS / BFS 的差異
- BFS layer 與無權圖最短路
- Grid BFS、多源 BFS
- DAG 與 topological sort
- Tree 的 parent、depth、subtree 與基本 traversal

**驗收：** 能說明為何普通 queue BFS 得到最短路，以及何時它不再成立。

### 階段 6：Greedy 與正確性證明

**目標：** 不只提出局部選擇，還能證明它不會錯失最佳解。

- 排序型 greedy、區間選擇
- 用 priority queue 維護候選
- exchange argument、stay-ahead、反證法
- 主動尋找 greedy 反例

「每次挑看起來最好」不是演算法，只是一種樂觀的人生態度。

**驗收：** 每個 greedy 解法至少能給一段交換論證；若證不出來，回頭考慮 DP 或搜尋。

### 階段 7：Dynamic Programming

**目標：** 從暴力遞迴找出重複子問題，設計可計算的狀態。

- state、transition、base case、計算順序、答案位置
- memoization 與 bottom-up
- linear DP：最大子段和、選／不選
- grid DP
- 0/1 knapsack、unbounded knapsack
- LCS 等基礎二維 DP
- 空間壓縮（理解依賴後再做）

**驗收：** 能用一句完整的話定義 `dp[...]`；能從狀態數 × 每狀態轉移成本算複雜度。

### 階段 8：分治與加權圖

**目標：** 補齊 APCS 高級題常見的演算法組合能力。

- merge sort、inversion count、recurrence 的直觀分析
- Dijkstra（非負邊權）
- DSU 與 Kruskal MST
- 綜合題：建模＋前處理／greedy／DP／graph 的組合

**驗收：** 能根據圖的邊權與規模選 BFS 或 Dijkstra；能說明 DSU 維護的集合意義。

---

## B. 競程延伸：APCS 穩定後再學

以下很有用，但不該擠壓 APCS 基礎題與中級題的訓練時間：

- Fenwick Tree：point update + prefix/range query
- Segment Tree：更一般的 range query / update
- monotonic stack / queue
- shortest path 進階、SCC、LCA
- tree DP、bitmask DP
- 字串演算法、數論與計算幾何

選擇原則：**遇到既有工具明確過不了的限制，再學下一個工具。** 收藏模板不會轉化成分數。

---

## 六題的建議使用方式

| 題目 | 放置階段 | 主要訓練目的 |
| --- | --- | --- |
| q181 等紅綠燈 | 0 | 條件、迴圈、時間／狀態模擬 |
| q836 小心陷阱 | 0 | while 模擬、更新順序、終止條件 |
| q182 字串操作 | 1 | 字串索引與逐步操作 |
| q837 轉盤得分 | 1 | 陣列／環狀索引與模擬 |
| r489 航空拍照圖 | 1 | 二維資料與 grid 規則處理 |
| r490 商品包裝地 | 1 | 字串驗證、分組計數與最大值 |

這六題都是前兩題型取向，適合檢查基礎是否穩固，但**不足以代表完整 APCS 路線**。若目標是實作三級以上，後續必須加入第三、四題等級的 DFS/BFS、greedy、DP 與圖論題。

---

## 訓練節奏與升級條件

每個階段建議使用「少量觀念＋大量刻意練習」：

- 20%：讀觀念與範例
- 60%：獨立解題，先不看提示
- 20%：訂正、重寫與整理反例

不要用固定週數假裝每個人的起點相同。符合以下條件再升級：

1. 同類型新題能獨立完成約 70%。
2. 能解釋演算法為何正確以及時間／空間複雜度。
3. 一週後不看舊碼可以重寫代表題。
4. 90 分鐘混合練習中，基礎題不因 index、overflow、輸入格式等錯誤失分。

每 2–3 週安排一次完整模擬賽。賽後分類失分原因：讀題、建模、演算法、實作、複雜度或時間管理。只記 WA 題號沒有用；你需要知道自己是在哪個齒輪掉牙。

---

## 目標導向的停靠點

- **目標：先拿實作 2 級**：優先練熟階段 0–2，尤其是模擬、陣列、字串與除錯。
- **目標：穩定實作 3 級**：完成階段 0–6，強化 DFS/BFS、枚舉、binary search 與 greedy。
- **目標：挑戰實作 4–5 級／資競**：完成階段 7–8，再依弱點進入競程延伸。

路線不是鐵軌。做題暴露出的弱點，永遠比「目前看到第幾章」更值得決定下一步。
