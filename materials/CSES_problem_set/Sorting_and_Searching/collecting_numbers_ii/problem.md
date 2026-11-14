---
title: Collecting Numbers II
difficulty: hard
source: CSES
problemId: Collecting Numbers II
order: 110
topics: [array, amortized-analysis]
patterns: [position-array, local-update]
techniques: [index-mapping]
---

交換兩個值只會影響它們附近的相鄰數值關係，因此每次查詢只需更新常數個斷點。

!!! note "版本狀態"
    `cnt_by_gemini.cpp` 是最完整版本；其他檔案保留索引和值混淆等修正歷程。
