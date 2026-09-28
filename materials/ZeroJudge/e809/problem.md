---
title: "e809. 1－字母排序 (Letters)"
source: ZeroJudge
problemId: e809
difficulty: medium
order: 14
topics: [string, prefix-sum, binary-search]
patterns: [weighted-prefix-selection]
techniques: [frequency-table, lower-bound]
prerequisites: [prefix-sum, binary-search]
pitfalls: [prefix-sentinel, one-based-rank, off-by-one]
complexity: {time: "O(|x| + |y| + q log |x|)", space: "O(|x|)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=e809)

先統計字串 `y` 中每個字母的權重，再依字串 `x` 的順序累積權重。每筆查詢要找累積序列中第 `k` 個位置落在哪個字母。

## 解法

用長度 26 的陣列保存每個大寫字母在 `y` 中出現次數。接著建立 `x` 的加權前綴和，並在最前面放入 0。對查詢值 `k`，以 `lower_bound` 找第一個前綴和 `≥ k` 的索引。

## 為什麼可以二分搜尋

每個字母權重都是非負數，所以前綴和單調不減；「第一個至少到達 k 的位置」因此具有明確邊界。

## 索引對應

前綴陣列比 `x` 多一格：`prefix[i]` 代表 `x` 前 `i` 個字母的總權重。因此找到索引 `i` 後，對應字元是 `x[i-1]`。

## 常見錯誤

- 忘記前綴開頭的 0，導致索引意義改變。
- 使用 `upper_bound`，當累積值剛好等於查詢時跳到下一格。
- 找到 prefix 索引後直接取 `x[i]`，整體偏一格。

## 複雜度

建表與前綴為線性，每筆查詢 $O(\log |x|)$。

