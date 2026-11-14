---
title: Traffic Lights
difficulty: medium
source: CSES
problemId: Traffic Lights
order: 113
topics: [set, multiset]
patterns: [predecessor-successor, local-update]
techniques: []
---

用 ordered set 找新燈的左右鄰居，再用 multiset 維護所有區間長度。

!!! note "版本狀態"
    `tl_by_gemini.cpp` 是標準版本；刪除 multiset 的單一舊區間時必須傳入 iterator。
