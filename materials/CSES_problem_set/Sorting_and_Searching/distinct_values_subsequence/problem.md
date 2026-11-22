---
title: Distinct Values Subsequences
difficulty: medium
source: CSES
problemId: Distinct Values Subsequences
order: 115
topics: [dynamic-programming, counting, map]
patterns: [choose-or-skip]
techniques: [modular-arithmetic]
---

以 `total` 與依數值索引的 `used[x]` 維護子序列計數狀態，逐項更新並對 `1,000,000,007` 取模；最後扣除空子序列。
