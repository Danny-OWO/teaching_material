---
title: "b923. stack 堆疊的模板題"
source: ZeroJudge
problemId: b923
difficulty: easy
order: 1
topics: [stack, data-structure]
patterns: [last-in-first-out]
techniques: [push-pop-top]
prerequisites: [array]
pitfalls: [empty-stack, command-parsing]
complexity: {time: "O(q)", space: "O(q)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=b923)

這題用三種操作練習 stack：放入元素、查看頂端、移除頂端。Stack 的規則是 **Last In, First Out**，最後放入的元素最先被取出。

## 解法

用容器尾端當作 stack 頂端：`append` 對應 push，`[-1]` 對應 top，`pop()` 對應 pop。每個指令只影響最上方，不必搬動其他元素。

## 核心不變量

處理完任意筆指令後，容器由前到後保存 stack 從底到頂的所有元素，而且順序和操作歷史完全一致。

## 常見錯誤

- 把 stack 當 queue，從容器前端刪除。
- 在空 stack 上存取頂端。即使題目保證操作合法，也應知道這是未定義行為的來源。
- 讀指令時假設每行欄位數相同；push 指令通常會多一個值。

## 複雜度

每個操作平均為 $O(1)$，總時間 $O(q)$；最壞保存所有推入元素，空間 $O(q)$。

