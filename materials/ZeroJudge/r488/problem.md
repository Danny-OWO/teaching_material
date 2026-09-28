---
title: "r488. 1－彗星撞擊"
source: ZeroJudge
problemId: r488
difficulty: medium
order: 12
topics: [matrix, simulation]
patterns: [range-effect-simulation]
techniques: [bounded-square-scan, state-update]
prerequisites: [matrix-indexing]
pitfalls: [row-column-swap, boundary, conditional-effect]
complexity: {time: "O(total affected area)", space: "O(rc)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=r488)

網格同時保存恐龍數量與地形高度。每次彗星影響一個正方形範圍：若範圍內有恐龍就清除；完全沒有擊中恐龍時，才降低該範圍高度。

## 解法

用兩張矩陣分別保存恐龍數量與高度。對每次撞擊計算半徑 `(s-1)/2`，枚舉中心周圍合法格子，先統計並清除恐龍；只有擊殺數為 0 時，再掃同一區域降低高度。

## 核心不變量

每次事件結束後，恐龍矩陣與高度矩陣都完整反映截至目前的所有撞擊，且總恐龍數同步扣除該次實際擊殺量。

## 常見錯誤

- 輸入 `(row, col)` 卻用成 `(x, y)`，導致非方形測資才爆炸。
- 範圍超出邊界時沒有裁切。
- 擊中恐龍的同一次撞擊仍降低高度。
- 每格只用布林值，忽略同一位置可能有多隻恐龍。

## 複雜度

若第 `i` 次範圍邊長為 $s_i$，時間為 $O(\sum s_i^2)$，兩張矩陣空間 $O(rc)$。

