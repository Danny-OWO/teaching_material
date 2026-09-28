---
title: "f174. m6a2－蛋糕 (Cake)"
source: ZeroJudge
problemId: f174
difficulty: hard
order: 16
topics: [prefix-sum, deque, dynamic-window]
patterns: [maximum-subarray-with-length-limit]
techniques: [monotonic-queue]
prerequisites: [prefix-sum, deque]
pitfalls: [negative-values, expired-index, update-order]
complexity: {time: "O(n)", space: "O(k)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=f174)

要求長度不超過 `k` 的連續區間最大總和。若元素可能為負數，一般「左界固定跟著右界走」的 sliding window 不足以找到最佳答案。

## 轉成前綴和

區間 `[l, r)` 的和是 `pre[r] - pre[l]`。對固定右端 `r`，要讓答案最大，就要在合法範圍 `r-k ≤ l < r` 中找到最小的 `pre[l]`。

## 單調佇列

Deque 保存候選前綴索引，而且對應值單調遞增：

1. 從前端移除太舊、已超出長度限制的索引。
2. 用前端最小前綴計算目前答案。
3. 從後端移除不小於 `pre[r]` 的值，再加入 `r`。

較大的舊前綴既不更小、又不更新，未來永遠不會比新前綴更好。

## 常見錯誤

- 套用只適合非負數的普通 sliding window。
- 在計算答案前先把 `r` 加入 deque，錯誤允許空區間。
- 過期判斷差一格：合法條件是 `l ≥ r-k`。
- Deque 存前綴值而不是索引，失去判斷是否過期的能力。

## 複雜度

每個索引最多進出 deque 一次，時間 $O(n)$，deque 最多保留 $O(k)$ 個索引。

