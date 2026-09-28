---
title: "c130. 00574－Sum It Up"
source: ZeroJudge
problemId: c130
difficulty: medium
order: 13
topics: [dfs, backtracking, subset-sum]
patterns: [choose-or-skip, enumerate-solutions]
techniques: [backtracking, deduplication]
prerequisites: [recursion]
pitfalls: [duplicate-solution, missing-backtrack, output-order]
complexity: {time: "O(2ⁿ · n)", space: "O(2ⁿ · n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=c130)

從最多 12 個正整數中選取若干個，使總和等於目標，並輸出所有不同組合。每個輸入位置只能使用一次，即使數值相同也代表不同選擇來源。

## 解法

DFS 在每個位置做兩個選擇：選或不選。狀態包含目前索引、累積和與已選數列。達到目標時保存答案；總和超過目標或索引用完時停止。

## 回溯結構

```text
加入 nums[i]
遞迴下一層
pop_back() 還原
再探索不加入的分支
```

「還原」不是裝飾。如果忘記 pop，兄弟分支會繼承不屬於自己的選擇。

## 去重與順序

相同數值可能來自不同位置，因此不同選取路徑會得到相同算式。可將每個答案正規化後排序、`unique`；更進階的作法是在同一 DFS 層直接跳過重複值。

## 常見錯誤

- 找到一組答案就停止，題目要求全部。
- 去重時使用無序容器，破壞指定輸出順序。
- 全域答案沒有在下一筆測資前清空。
- 標題輸出 `Sum`／`Sums` 拼字不符題目。

## 複雜度

最多枚舉 $2^n$ 個子集，每組整理可能需 $O(n)$，時間約 $O(2^n n)$。

