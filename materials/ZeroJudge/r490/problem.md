---
title: "r490. 3－商品包裝地"
source: ZeroJudge
problemId: r490
difficulty: easy
order: 8
topics: [string, counting, simulation]
patterns: [validation-and-frequency]
techniques: [check-digit, frequency-array]
prerequisites: [string-indexing]
pitfalls: [leading-zero, check-digit, tie-breaking]
complexity: {time: "O(nL)", space: "O(1)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=r490)

逐筆驗證商品編碼，只統計合法編碼的前三碼產地代號，最後輸出出現最多的代號與數量。

## 解法

將奇偶位置的數字分別加總，依題目規則計算檢查碼。合法時把前三個字元轉成 0 到 999 的索引，更新頻率陣列；最後由小到大掃描找最大值。

## 核心不變量

處理完前 `i` 筆後，`count[p]` 等於其中所有合法且產地代號為 `p` 的商品數。

## 常見錯誤

- 把前三碼當整數輸出，遺失前導零，例如 `007` 變成 `7`。
- 搞反 0-based 索引的奇偶權重。
- 平手時更新條件寫成 `>=`，導致選到較大的代號；由小到大掃描配合 `>` 才會保留最小者。
- 驗證公式只檢查一種等價形式，漏掉和為 10 的邊界。

## 複雜度

每個編碼長度固定，總時間可視為 $O(n)$；頻率陣列固定 1001 格，空間 $O(1)$。

