---
title: "i401. 3－雷射測試"
source: ZeroJudge
problemId: i401
difficulty: hard
order: 17
topics: [geometry, binary-search, simulation]
patterns: [spatial-index-by-axis, ray-tracing]
techniques: [sorted-buckets, lower-bound, upper-bound]
prerequisites: [binary-search, coordinate]
pitfalls: [direction-transition, strict-next, coordinate-offset]
complexity: {time: "O(n log n + h log n)", space: "O(n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=i401)

雷射沿水平或垂直方向前進，撞到鏡子後依 `/` 或 `\` 改變方向，求離開場地前撞到幾面鏡子。逐單位移動在座標很大時不可行，應直接跳到同一直線上的下一面鏡子。

## 空間索引

- `x_based[x]`：固定 x 的所有鏡子，依 y 排序，用於上下移動。
- `y_based[y]`：固定 y 的所有鏡子，依 x 排序，用於左右移動。

每次依方向使用 `upper_bound` 找嚴格較大的下一點，或 `lower_bound` 後退一格找嚴格較小的上一點。找不到就表示雷射離開場地。

## 狀態

狀態只有 `(x, y, direction)`。撞到鏡子後先更新座標、計數，再依鏡面種類轉向。把四種方向與兩種鏡面整理成轉移表，會比散落的條件判斷更不容易錯。

## 常見錯誤

- 查到目前所在鏡子本身，造成無限循環；搜尋必須是嚴格下一個位置。
- 負 y 直接當陣列索引，忘記加 offset。
- `/` 與 `\` 的方向轉換背反。
- 每次重新掃描所有鏡子，時間退化成 $O(nh)$。

## 複雜度

所有 bucket 排序總計 $O(n\log n)$；每次撞擊二分搜尋，若撞擊 `h` 次則為 $O(h\log n)$。

