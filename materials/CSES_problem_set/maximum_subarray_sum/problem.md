---
title: Maximum Subarray Sum
difficulty: easy
source: CSES
problemId: Maximum Subarray Sum
order: 106
topics: [dynamic-programming, array]
patterns: [maximum-subarray]
techniques: [kadane]
---

Kadane 演算法維護「以目前位置結尾的最佳連續和」，並同步更新全域答案。

!!! note "版本狀態"
    `mss_1.cpp` 是標準版本；`mss.cpp` 的 prefix-sum 嘗試尚不完整。
