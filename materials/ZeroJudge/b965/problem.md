---
title: "b965. 2－矩陣轉換"
source: ZeroJudge
problemId: b965
difficulty: medium
order: 10
topics: [matrix, simulation]
patterns: [reverse-operations]
techniques: [rotation, vertical-flip]
prerequisites: [matrix-indexing]
pitfalls: [operation-order, dimension-swap, rotation-direction]
complexity: {time: "O(mrc)", space: "O(rc)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=b965)

已知矩陣經過一連串旋轉與翻轉後的結果，要求還原原矩陣。關鍵不是照指令再做一次，而是**反向執行每個操作的逆操作**。

## 解法

先把操作序列倒過來。上下翻轉的逆操作仍是上下翻轉；順時針旋轉的逆操作則是逆時針旋轉，也可用三次順時針旋轉完成。

## 座標思考

旋轉後 row、column 數量會互換。建立新矩陣時，先決定新尺寸，再推導舊座標映射到哪一格；不要邊寫迴圈邊猜索引。

## 核心不變量

倒序處理完最後 `t` 個操作後，目前矩陣等於原正向流程執行到倒數第 `t` 個操作以前的狀態。

## 常見錯誤

- 操作順序沒有反轉。
- 旋轉後忘記交換 `r` 與 `c`。
- 把水平翻轉與垂直翻轉混為一談。
- 就地旋轉非方陣，造成尚未讀取的資料被覆寫；建立新矩陣較安全。

## 複雜度

每個操作掃描整張矩陣，時間 $O(mrc)$，新矩陣空間 $O(rc)$。

