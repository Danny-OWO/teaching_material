---
title: "200. Number of Islands｜島嶼數量"
source: LeetCode
problemId: 200
difficulty: medium
order: 4
topics: [matrix, graph, dfs]
patterns: [connected-components, flood-fill]
techniques: [iterative-dfs, in-place-marking]
prerequisites: [stack, grid-traversal]
pitfalls: [double-counting, boundary-check, recursion-depth]
complexity:
  time: "O(rows × cols)"
  space: "O(rows × cols) worst case"
---

`'1'` 代表陸地、`'0'` 代表水；上下左右相鄰的陸地屬於同一座島。求島嶼數量。

## 辨識線索

把每個陸地格子看成頂點，上下左右的鄰接關係看成邊，題目就變成：圖中有幾個 connected components（連通分量）。

這個建模比背誦「網格題用 DFS」更重要。DFS 只是走訪工具；真正的問題結構是連通分量。

## 演算法

逐格掃描：

1. 遇到水或已拜訪的格子，略過。
2. 遇到尚未拜訪的陸地，答案加一。
3. 從該格開始 flood fill，把整座島都標成水。

```text
1 1 0 0       x x 0 0
1 0 0 1  -->  x 0 0 1
0 0 1 1       0 0 1 1

第一次 flood fill 只消掉左上角島嶼；
之後掃到右側陸地時，才計入第二座島。
```

## 核心不變量

掃描位置之前的所有格子，都不再包含尚未計數的陸地。每次發現 `'1'` 時，它不可能屬於先前算過的島，否則早已被 flood fill 標記。

## 正確性

每次增加答案時，起點屬於一個從未計數的連通分量；完整 DFS 會且只會標記該分量中的格子。不同增加操作對應不同分量，每個分量又一定會在其第一個被掃到的格子觸發一次，因此答案恰為島嶼數量。

## 常見錯誤

- 每看到一個 `'1'` 就加一，算到的是陸地格數，不是島數。
- 先存取 `grid[nr][nc]` 才檢查邊界。
- 在大型網格使用遞迴 DFS，可能耗盡 call stack；此解答刻意使用顯式 stack。

## 延伸思考

若陸地也允許斜角相連，只有鄰居方向改變；若要動態加入陸地並即時查詢島數，DFS 就不夠漂亮了，該考慮 Union-Find。

