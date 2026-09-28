---
title: "c700. 壞掉的隊列 (queue)"
source: ZeroJudge
problemId: c700
difficulty: medium
order: 15
topics: [stack, queue, amortized-analysis]
patterns: [two-stack-queue]
techniques: [lazy-transfer]
prerequisites: [stack, queue]
pitfalls: [transfer-every-time, wrong-order, empty-pop]
complexity: {time: "O(q) amortized", space: "O(q)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=c700)

只能使用 stack 操作模擬 queue。Queue 要先進先出，stack 卻是後進先出；第二個 stack 用來再反轉一次，順序便會恢復。

## 解法

- push：把新元素放進輸入 stack `s1`。
- pop：若輸出 stack `s2` 為空，把 `s1` 全部搬到 `s2`；接著從 `s2` 彈出。

只在 `s2` 空時搬運是關鍵。若每次 pop 都來回搬，正確但會把時間複雜度做爛。

## 核心不變量

`s2` 頂端是目前 queue 最前面的元素；`s1` 保存較晚加入、尚未翻轉的元素。Queue 的完整順序等於 `s2` 由頂到底，再接 `s1` 由底到頂。

## 攤銷分析

每個元素最多被 push 進 `s1`、搬到 `s2`、再 pop 一次，總操作次數是常數倍。因此單次雖可能搬 $O(n)$ 個元素，整串指令仍是 $O(q)$。

## 常見錯誤

- `s2` 尚有元素時又搬入 `s1`，破壞先後順序。
- 看到某次操作是 $O(n)$ 就誤判總時間為 $O(qn)$，忽略每個元素只搬一次。
- 忽略題目要求輸出的操作代碼順序。

