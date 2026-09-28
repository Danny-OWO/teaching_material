---
title: "410. Split Array Largest Sum｜分割陣列的最大值"
source: LeetCode
problemId: 410
difficulty: hard
order: 5
topics: [array, binary-search, greedy]
patterns: [binary-search-on-answer, monotonic-feasibility]
techniques: [greedy-partition, lower-bound]
prerequisites: [binary-search, prefix-sum, greedy]
pitfalls: [wrong-search-bounds, overflow, exact-vs-at-most]
complexity:
  time: "O(n log(sum(nums)))"
  space: "O(1)"
---

把非負整數陣列切成 `k` 個非空、連續子陣列，使各段總和的最大值盡可能小。

## 為什麼這題難

題目問的是「如何切」，但直接枚舉切點會爆炸。關鍵轉向是先猜答案 `limit`，改問一個容易判斷的問題：

> 能不能讓每一段的總和都不超過 `limit`，並用至多 `k` 段完成？

如果 `limit` 可行，更大的限制一定也可行：

```text
不可行 不可行 不可行｜可行 可行 可行
                    ↑ 找第一個可行值
```

這個真假序列具有單調性，因此可以對**答案空間**做 lower-bound binary search。

## 搜尋範圍

- 下界：`max(nums)`，任何一個元素都不能被拆開。
- 上界：`sum(nums)`，完全不切時必定可行。

比起寫 `0` 到某個神祕大常數，這兩個界線同時正確而且緊。

## 可行性檢查：貪心切割

由左到右，能放進當前段就放；放不下才開新段。這會產生在限制 `limit` 下的**最少段數**，因為提早切割不可能讓後面的元素需要更少段。

```text
nums = [7, 2, 5, 10, 8], limit = 18

[7, 2, 5]  sum = 14
[10, 8]     sum = 18

需要 2 段，所以對 k = 2 可行。
```

## 核心不變量

二分搜尋採用閉區間 `[left, right]`，真正答案始終位於其中。當 `mid` 可行時，答案可能等於 `mid`，所以保留它並令 `right = mid`；不可行時則令 `left = mid + 1`。

這和第 704 題找「剛好相等」的閉區間寫法不同。兩段程式碼只差幾個字，語意卻完全不同——二分搜尋最愛用這種地方收學費。

## 為什麼「至多 k 段」足夠

如果貪心只用了少於 `k` 段，可以繼續把某些含多個元素的段切開；元素非負，切開後的段和不會變大。只要 `k ≤ n`，便能得到恰好 `k` 個非空子陣列。

## 常見錯誤

- 把下界設成 `0`，浪費搜尋且忽略單一元素不可分割。
- `sum(nums)` 使用 `int` 而溢位；答案與累加值使用 `long long`。
- 可行時寫 `right = mid - 1`，最後卻直接回傳 `left`，混用了兩種二分模板。
- 沒注意「非負整數」是貪心正確的重要條件；允許負數後，延後切割不再總是安全。

## 延伸思考

Painter's Partition、分配書本、最小化最大工作量，通常只是換皮版本。先尋找「答案越大是否越容易可行」，比背題名可靠得多。

