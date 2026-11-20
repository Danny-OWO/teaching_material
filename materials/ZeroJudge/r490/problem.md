---
title: "r490. 3－商品包裝地"
source: ZeroJudge
problemId: r490
difficulty: easy
order: 8
topics: [string, counting, simulation]
patterns: [validation-and-frequency]
techniques: [check-digit, frequency-counting]
prerequisites: [string-indexing]
pitfalls: [leading-zero, check-digit]
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
- 題目保證答案唯一，且至少有一組合法條碼，不需要另外制定平手規則。
- 驗證公式只檢查一種等價形式，漏掉和為 10 的邊界。

目前 `r490.py` 的輸出只補一次零，產地 `007` 會印成 `07`。練習時請改用 `str(tag).zfill(3)` 或整數格式化 `f"{tag:03d}"`，不要直接把現有程式當成已驗證的標準答案。

## 複雜度

每個編碼長度固定，總時間可視為 $O(n)$；頻率陣列固定 1001 格，空間 $O(1)$。

