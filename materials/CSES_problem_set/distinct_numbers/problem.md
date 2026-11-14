---
title: Distinct Numbers
difficulty: easy
source: CSES
problemId: Distinct Numbers
order: 101
topics: [sorting, counting, array]
patterns: []
techniques: [deduplication, linear-scan]
---

排序後計算相鄰值改變的次數。

!!! warning "原始版本提醒"
    `holder = 0` 被當成哨兵值；若輸入包含 0，這個版本會漏算。
