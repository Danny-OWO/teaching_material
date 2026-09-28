---
title: "1. Two Sum｜兩數之和"
source: LeetCode
problemId: 1
difficulty: easy
order: 1
topics: [array, hash-table]
patterns: [complement-lookup]
techniques: [single-pass-hash-map]
prerequisites: [array, unordered-map]
pitfalls: [duplicate-values, insert-before-query]
complexity:
  time: "O(n)"
  space: "O(n)"
---

給定整數陣列 `nums` 與目標值 `target`，找出兩個不同位置，使它們的值相加等於 `target`。

## 辨識線索

題目要找一組配對，而且看到目前的數字 `x` 後，另一半已經被唯一決定為 `target - x`。這就是 **complement lookup（查找互補值）**。

暴力解會枚舉所有 `(i, j)`，時間是 $O(n^2)$。真正的轉折不是「用 hash map 比較快」，而是把問題改寫成：

> 掃到 `x` 時，我以前是否看過 `target - x`？

## 核心不變量

處理索引 `i` 以前，`seen` 儲存的恰好是索引 `[0, i)` 的值與位置。因此如果補數已在 `seen` 中，找到的位置一定和 `i` 不同。

```text
nums = [2, 7, 11, 15], target = 9

i = 0, x = 2, 需要 7：沒看過 → 記錄 2
i = 1, x = 7, 需要 2：看過了 → 回傳 [0, 1]
```

## 正確性

假設答案位置是 `i < j`。當掃描到 `j` 時，`nums[i]` 已經存在 `seen`，而查詢的補數正是 `target - nums[j] = nums[i]`，所以演算法必定找到答案。

## 常見錯誤

- 先把目前元素放入 map 再查詢，當 `target = 2 * nums[i]` 時可能錯用同一位置兩次。
- 把「值」當成答案回傳；題目要的是索引。
- 認為 hash table 是 $O(1)$ 的魔法。這裡指的是平均時間，最壞情況仍取決於雜湊品質。

## 延伸思考

若陣列已排序，你能否不用額外 $O(n)$ 空間？提示：左右指標的和具有單調性。
