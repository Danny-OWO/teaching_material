---
title: "m932. 2－蜜蜂觀察"
source: ZeroJudge
problemId: m932
difficulty: easy
order: 7
topics: [simulation, grid, set]
patterns: [direction-vector]
techniques: [hex-grid-movement, boundary-check]
prerequisites: [array, coordinate]
pitfalls: [row-direction, invalid-move, distinct-count]
complexity: {time: "O(g log g)", space: "O(g)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=m932)

在六角形格網上依指令移動蜜蜂，輸出每一步觀察到的字元，最後計算看過多少種不同字元。

## 解法

把六個方向整理成 `delta_r`、`delta_c`，每次用目前座標加上位移得到候選位置。候選位置合法才更新座標；越界時留在原地，仍記錄目前格子的字元。

## 核心不變量

每輪結束後，`pos_r, pos_c` 一定指向合法格子，而 `words` 恰好包含目前為止每一步觀察到的結果。

## 常見錯誤

- 畫面向上時 row 應減少，卻把正負方向寫反。
- 越界時不更新座標，卻忘了仍要輸出原位置字元。
- 題目問不同種類時直接輸出走訪次數；應使用 set 去重。

## 複雜度

移動模擬 $O(g)$；用平衡樹 set 去重為 $O(g\log g)$，若字元範圍固定也可用布林陣列做到 $O(g)$。

