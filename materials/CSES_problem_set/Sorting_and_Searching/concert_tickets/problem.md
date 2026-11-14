---
title: Concert Tickets
difficulty: medium
source: CSES
problemId: Concert Tickets
order: 104
topics: [multiset, binary-search, greedy]
patterns: [predecessor-successor]
techniques: [upper-bound]
---

標準解法會用 `multiset::upper_bound` 找不超過顧客預算的最高票價，售出後刪除一張。

!!! danger "未完成"
    ZIP 內的 `ct.cpp` 停在空的 `for ()`，目前無法編譯；此頁保留原始進度，不把半成品包裝成答案。
