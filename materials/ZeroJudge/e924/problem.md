---
title: "e924. pC－括號配對"
source: ZeroJudge
problemId: e924
difficulty: easy
order: 5
topics: [string, stack]
patterns: [typed-delimiter-matching]
techniques: [stack-simulation, encoding]
prerequisites: [stack]
pitfalls: [wrong-type, empty-stack, leftover-opening]
complexity: {time: "O(n)", space: "O(n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=e924)

這題把括號擴充為 `() [] {} <>`。除了數量與順序，關閉符號的種類也必須和最近尚未關閉的左括號一致。

## 解法

左括號推入代表種類的正整數，右括號轉成相反的負整數。若 `stack.top() + tag == 0` 就代表同類配對，否則立即判定不合法。

## 核心不變量

Stack 從底到頂保存目前所有未關閉的左括號。下一個右括號只能關閉頂端，因為括號結構必須正確巢狀。

## 常見錯誤

- 看到任意右括號就彈出，沒有檢查種類。
- 在空 stack 上讀取 top。
- 掃描結束後 stack 非空仍判定合法。
- 用大量互相獨立的 `if`，讓一個字元被重複分類；用 mapping 或 `switch` 更清楚。

## 複雜度

時間 $O(n)$，最壞所有字元都是左括號，空間 $O(n)$。

