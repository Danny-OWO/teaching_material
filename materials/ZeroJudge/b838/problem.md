---
title: "b838. 104北二2－括號問題"
source: ZeroJudge
problemId: b838
difficulty: easy
order: 4
topics: [string, stack]
patterns: [balanced-parentheses]
techniques: [stack-simulation]
prerequisites: [stack]
pitfalls: [early-closing, leftover-opening]
complexity: {time: "O(n)", space: "O(n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=b838)

判斷單一種類的括號是否完整配對；合法時輸出配對數，不合法則輸出 0。

## 解法

讀到 `(` 就推入 stack；讀到 `)` 時必須有尚未配對的左括號，才能彈出並增加配對數。掃描結束後 stack 也必須為空。

## 核心不變量

掃描到任意位置時，stack 大小等於目前「已出現但還沒被右括號配對」的左括號數量。

## 為什麼不能只數總數

`) (` 的左右括號數量相同，順序卻不合法。任何前綴中，右括號數都不能超過左括號數；stack 為空時遇到 `)` 正是在偵測這件事。

## 常見錯誤

- 只檢查左右括號總數相等。
- 遇到非法右括號後仍繼續計算。
- 最後忘記檢查是否留下未配對的 `(`。

## 複雜度

每個字元進出 stack 至多一次，時間 $O(n)$，最壞空間 $O(n)$。

