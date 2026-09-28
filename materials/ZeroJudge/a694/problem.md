---
title: "a694. 吞食天地二"
source: ZeroJudge
problemId: a694
difficulty: medium
order: 9
topics: [matrix, prefix-sum]
patterns: [rectangle-sum-query]
techniques: [two-dimensional-prefix-sum, inclusion-exclusion]
prerequisites: [prefix-sum, matrix]
pitfalls: [one-based-input, boundary, add-back-overlap]
complexity: {time: "O(n² + m)", space: "O(n²)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=a694)

矩陣不變、矩形總和查詢很多次時，逐格重算會重複大量工作。二維前綴和先花一次 $O(n^2)$ 預處理，之後每個矩形只需常數時間。

## 前綴定義

`P[i][j]` 表示左上角 `(0,0)` 到 `(i,j)` 的總和：

```text
P[i][j] = A[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]
```

左方與上方重疊的區域被加了兩次，所以必須減回一次。

## 查詢

矩形 `(a,b)` 到 `(c,d)` 的答案是右下大矩形，減掉上方與左方，再把被減兩次的左上角交集加回：

```text
P[c][d] - P[a-1][d] - P[c][b-1] + P[a-1][b-1]
```

## 常見錯誤

- 忘記輸入座標從 1 開始，陣列從 0 開始。
- `a=0` 或 `b=0` 時讀到負索引。
- 只減上方與左方，忘記把重疊區加回。
- 總和可能超過 `int`，使用 `long long`。

## 複雜度

預處理 $O(n^2)$，每筆查詢 $O(1)$，總時間 $O(n^2+m)$，空間 $O(n^2)$。

