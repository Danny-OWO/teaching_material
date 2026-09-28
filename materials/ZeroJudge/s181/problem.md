---
title: "s181. 3－校運代表隊"
source: ZeroJudge
problemId: s181
difficulty: hard
order: 18
topics: [dfs, backtracking, combinatorics]
patterns: [kth-valid-combination, constraint-tracking]
techniques: [lexicographic-dfs, pruning]
prerequisites: [recursion, combination]
pitfalls: [enumeration-order, state-rollback, class-index]
complexity: {time: "exponential worst case", space: "O(k + n + m)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=s181)

依學生編號升序枚舉 `k` 人隊伍，限制同專長不可重複、每班最多兩人，輸出第 `t` 組合法組合。這不只是找任一解；**枚舉順序本身也是答案的一部分**。

## DFS 狀態

- `depth`：已選幾人。
- `start`：下一位可考慮的最小索引，保證編號遞增且不重複。
- `had_tal`：哪些專長已使用。
- `had_cla`：每班已選人數。
- `choosed`：目前組合。

由小到大嘗試學生，合法才選入；遞迴回來後必須撤銷專長與班級計數。

## 剪枝

若「已選人數 + 剩餘候選人數 < k」，即使全選也湊不滿，應立即返回。找到第 `t` 組時直接結束，避免枚舉無關的後續答案。

## 核心不變量

每次進入 DFS，`choosed` 嚴格遞增，所有專長互異，每班人數不超過 2；追蹤陣列與目前選擇完全一致。

## 常見錯誤

- 先探索「不選」分支，導致組合順序不符合題目的升序定義。
- 回溯時只 pop 學生，忘記還原專長或班級計數。
- 班級索引計算差一：第 `i` 位學生的班級要依每班 `r` 人換算。
- 找到答案後只離開一層遞迴，仍繼續搜尋與輸出。

## 複雜度

最壞仍需枚舉組合，屬指數時間；狀態追蹤讓每次合法性檢查為 $O(1)$，並可透過剪枝大幅減少實際節點。

