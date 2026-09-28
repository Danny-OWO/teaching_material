---
title: "c002. 10696－f91"
source: ZeroJudge
problemId: c002
difficulty: easy
order: 6
topics: [recursion, math]
patterns: [recursive-definition]
techniques: [direct-simulation]
prerequisites: [function-call, recursion]
pitfalls: [base-case, nested-recursion, output-format]
complexity: {time: "depends on n", space: "recursive call stack"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=c002)

McCarthy 91 函數定義為：`n > 100` 時回傳 `n - 10`；否則回傳 `f91(f91(n + 11))`。題目的重點是忠實翻譯遞迴定義與輸出格式。

## 解法

基底條件放在 `n > 100`，其餘情況直接做兩層遞迴呼叫。不要把內層與外層呼叫誤寫成相加或連續執行但遺失回傳值。

## 觀察

對所有 `n ≤ 100`，函數結果最後都會收斂到 91；`n > 100` 則是 `n - 10`。雖然可以利用結論直接輸出，照定義遞迴更能展示函數呼叫如何展開。

## 常見錯誤

- 把條件寫成 `n < 100`，漏掉 `n = 100`。
- 忘記終止輸入的 0 不應計算。
- 輸出空格與括號不符合指定格式。

## 複雜度

直接遞迴的呼叫次數取決於 `n`；在本題輸入範圍內可行。若只使用已證明的封閉形式，每筆可降為 $O(1)$。

