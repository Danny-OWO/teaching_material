---
title: "20. Valid Parentheses｜有效括號"
source: LeetCode
problemId: 20
difficulty: easy
order: 2
topics: [string, stack]
patterns: [matching-pairs, last-open-first-close]
techniques: [stack-simulation]
prerequisites: [string, stack]
pitfalls: [empty-stack, leftover-openings]
complexity:
  time: "O(n)"
  space: "O(n)"
---

判斷只包含 `()[]{}` 的字串是否括號種類與順序都正確。

## 辨識線索

最新打開的括號必須最先被關閉：最後進來、最先出去，正是 stack 的 LIFO 行為。

不要只計算左右括號數量。`([)]` 的數量完全平衡，結構卻是錯的；題目要求的是**巢狀順序**。

## 核心不變量

掃描到任意位置時，stack 從底到頂保存所有「已出現、但尚未配對」的左括號。

遇到右括號時：

1. stack 為空：沒有左括號能和它配對，立即失敗。
2. stack 頂端種類不符：最近打開的括號關錯了，立即失敗。
3. 種類相符：彈出頂端，繼續掃描。

## 正確性

每個右括號都只和最近尚未配對的左括號配對。若過程中沒有衝突，且最後 stack 為空，所有括號就形成完整且正確的巢狀配對；反之任何非法字串一定會在配對時衝突，或留下未關閉的左括號。

## 常見錯誤

- 在呼叫 `stack.top()` 前沒有先判斷 `empty()`。
- 掃描結束就回傳 `true`，忘記檢查是否還有左括號。
- 為三種括號寫六層 `if`。用「右括號 → 左括號」的 map 能直接描述規則。

## 延伸思考

如果輸入除了括號還包含普通字元，你會忽略它們，還是判定非法？這不是演算法問題，而是介面規格問題；不要偷偷替題目做決定。

