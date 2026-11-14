---
title: Collecting Numbers
difficulty: medium
source: CSES
problemId: Collecting Numbers
order: 109
topics: [array, counting]
patterns: [position-array]
techniques: [index-mapping, linear-scan]
---

建立 `pos[value]`；每當 `pos[x] > pos[x+1]`，就代表需要多開一輪。

!!! note "版本狀態"
    `cn_1.cpp` 與 `cn_by_gemini.cpp` 採正確的位置陣列方法；`cn.cpp` 是較早的錯誤嘗試。
