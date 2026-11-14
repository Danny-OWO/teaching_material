---
title: String Reorder
difficulty: hard
source: CSES
problemId: String Reorder
order: 20
topics: [string, greedy, counting]
patterns: [constructive, validation-and-frequency]
techniques: [frequency-counting]
---

逐步選擇不等於前一字元的候選，並優先處理即將超過剩餘容量一半的字元。

!!! note "版本狀態"
    ZIP 的整理筆記將 `string_reorder_1.cpp` 標為較合理版本；constructive 解法仍值得補 exhaustive 測試。
