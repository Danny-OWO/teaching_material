---
title: "e447. queue 練習"
source: ZeroJudge
problemId: e447
difficulty: easy
order: 2
topics: [queue, data-structure]
patterns: [first-in-first-out]
techniques: [enqueue-front-dequeue]
prerequisites: [array]
pitfalls: [empty-queue, wrong-end]
complexity: {time: "O(q)", space: "O(q)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=e447)

Queue 採用 **First In, First Out**：最早加入的元素最先離開。題目要求依指令加入、查詢隊首與移除隊首。

## 解法

C++ 使用 `queue`；Python 使用 `collections.deque`。加入發生在尾端，查詢與移除發生在前端。空 queue 的查詢要依題意輸出 `-1`，移除則不能硬做。

## 核心不變量

Queue 由前到後，始終等於所有「已加入但尚未移除」元素依加入時間排列的結果。

## 常見錯誤

- Python 用 list 的 `pop(0)`，每次都要搬動其餘元素，會退化成 $O(n)$。
- 把 `back()` 當成下一個要離開的元素。
- 空 queue 時仍呼叫 `front()` 或 `pop()`。

## 複雜度

每次操作為 $O(1)$，總時間 $O(q)$，空間為尚未離隊元素數量，最壞 $O(q)$。

