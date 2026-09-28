---
title: "e340. 差分練習"
source: ZeroJudge
problemId: e340
difficulty: easy
order: 3
topics: [array, difference-array]
patterns: [adjacent-difference]
techniques: [single-pass]
prerequisites: [array]
pitfalls: [first-element, index-shift]
complexity: {time: "O(n)", space: "O(n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=e340)

差分陣列記錄的不是每個位置的原值，而是「相對前一格改變多少」。定義 `diff[0] = a[0]`，其後 `diff[i] = a[i] - a[i-1]`。

## 解法

由左到右保存前一個原值 `prev`。讀到 `a[i]` 時輸出或記錄 `a[i] - prev`，再令 `prev = a[i]`。

## 為什麼可逆

原陣列就是差分陣列的前綴和：

```text
a[i] = diff[0] + diff[1] + ... + diff[i]
```

相鄰差分會讓中間項互相抵消，只留下 `a[i]`。

## 常見錯誤

- 第一格沒有前一項，忘記把基準視為 0。
- 更新 `prev` 太早，結果算成目前值減目前值。
- 混淆差分與前綴和：一個描述變化，一個累積還原。

## 複雜度

掃描一次為 $O(n)$；若直接輸出可做到 $O(1)$ 額外空間，保存答案則為 $O(n)$。

