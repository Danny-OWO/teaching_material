---
title: Towers
difficulty: medium
source: CSES
problemId: Towers
order: 112
topics: [binary-search, greedy, array]
patterns: [predecessor-successor]
techniques: [upper-bound]
---

維護排序後的塔頂，對每個方塊用 `upper_bound` 找第一個比它大的塔頂並替換。
