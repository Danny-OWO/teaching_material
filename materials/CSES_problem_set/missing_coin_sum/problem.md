---
title: Missing Coin Sum
difficulty: easy
source: CSES
problemId: Missing Coin Sum
order: 108
topics: [sorting, greedy]
patterns: [monotonic-prefix]
techniques: [greedy-smallest-first]
---

維護目前能連續組出的金額範圍 `[1, cur]`，並用排序後的下一枚硬幣擴張它。
