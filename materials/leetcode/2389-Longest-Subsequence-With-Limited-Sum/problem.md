---
title: "2389. Longest Subsequence With Limited Sum"
source: LeetCode
problemId: 2389
difficulty: easy
order: 1
topics: [array, sorting, prefix-sum, binary-search]
patterns: [maximize-count-under-budget, monotonic-prefix]
techniques: [greedy-smallest-first, upper-bound]
prerequisites: [sorting, prefix-sum]
pitfalls: [subsequence-vs-subarray, lower-bound-vs-upper-bound, integer-sum]
complexity:
  time: "O(n log n + m log n)"
  space: "O(n + m)"
---

對每個查詢上限 `query`，求能從 `nums` 選出的最長 subsequence，使總和不超過該上限。

## 你的解法骨架

```text
排序 nums → 建立前綴和 → 每筆 query 用 upper_bound
```

這裡最值得學的不是 `upper_bound` 語法，而是為什麼排序合法、又為什麼能貪心地從最小元素開始選。

## 辨識線索

題目只問最多能選幾個元素，不要求回傳原本的索引或選取順序。若要在固定預算內塞進最多元素，選較小的元素永遠不會比選較大的元素差。

排序後的前綴和：

```text
nums:    [1, 2, 4, 5]
prefix:  [1, 3, 7, 12]
```

`prefix[i]` 是選取前 `i + 1` 個最小元素的最低成本。因此問題轉成：有多少個前綴和 `≤ query`？

## 互動圖解

選擇不同查詢，觀察 `upper_bound` 回傳的是「第一個大於 query」的位置，而那個位置剛好等於可選元素數量。

<div class="algorithm-visualizer" data-prefix-query data-values="4,5,2,1" data-queries="3,10,21">
  <div class="visualizer-header">
    <strong>排序、前綴和與 upper_bound</strong>
    <span data-prefix-status>query = 3</span>
  </div>
  <div class="prefix-visualizer" data-prefix-cells></div>
  <p class="visualizer-message" data-prefix-message></p>
  <div class="visualizer-controls" data-prefix-controls></div>
</div>

## 正確性

對任何長度為 `t` 的可行 subsequence，其總和至少是排序後最小的 `t` 個元素總和，也就是 `prefix[t - 1]`。所以：

- 若 `prefix[t - 1] ≤ query`，前 `t` 小的元素構成可行解。
- 若 `prefix[t - 1] > query`，任何 `t` 個元素的選法都不可能可行。

因此最後一個不超過 `query` 的前綴長度，就是最佳答案。

## 你的程式碼值得注意的地方

- `upper_bound(prefix.begin(), prefix.end(), need)` 使用正確。若改成 `lower_bound`，當前綴和剛好等於 query 時會少算一個。
- 你額外建立 `prefix`，讓每筆查詢降到 $O(\log n)$；這比每次重新累加乾淨得多。
- 依題目限制，最大總和為 $10^9$，`int temp` 仍放得下。但若把這個模板搬去更大的限制，應優先改成 `long long`，不要讓 AC 帶來虛假的安全感。

## 常見誤判

`subsequence` 不等於 `subarray`。本題可以刪掉任意元素，因此排序後分析選哪些值是合理的；如果題目要求連續子陣列，排序會直接毀掉結構。

