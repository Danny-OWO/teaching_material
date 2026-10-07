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

## 逐步推演：找到第 2 組隊伍

用題目範例 #1：

```text
5 2 4 3 2
3 1 2 4 1 3 1 5
```

每班 4 人：1～4 號屬第 1 班，5～8 號屬第 2 班；第二行依序是各人的專長。以下依 `s181.py` 推演。`start` 是從 0 起算的**下一個候選索引**，學生編號則從 1 起算；「隊伍」只看 `choosed[:depth]`，`had_tal` 列出已用專長，`had_cla` 依序列出兩班已選人數。

1. `dfs(0, 0)`：隊伍 `[]`，`had_tal={}`，`had_cla=(0, 0)`。先選 1 號（專長 3），進入 `dfs(1, 1)`：隊伍 `[1]`，`had_tal={3}`，`had_cla=(1, 0)`。
2. 選 2 號（專長 1），進入 `dfs(2, 2)`：隊伍 `[1, 2]`，`had_tal={1, 3}`，`had_cla=(2, 0)`。第 1 班已滿兩人，3、4 號不能選；5、7 號的專長 1 已用，6 號的專長 3 已用。這些候選人在 Python 的 `for` 迴圈中被 `continue` 跳過，**沒有進入下一層 DFS**。
3. 選 8 號（專長 5），進入 `dfs(3, 8)`：隊伍 `[1, 2, 8]`，`had_tal={1, 3, 5}`，`had_cla=(2, 1)`。人數達 `k=3`，這是第 1 組合法隊伍；還沒到 `t=2`，因此返回。
4. 返回 `dfs(2, 2)` 後還原 8 號：隊伍 `[1, 2]`，`had_tal={1, 3}`，`had_cla=(2, 0)`。該層已無候選人，再返回 `dfs(1, 1)` 並還原 2 號：隊伍 `[1]`，`had_tal={3}`，`had_cla=(1, 0)`。`choosed` 陣列的舊格子不會清空，但不屬於 `choosed[:depth]`，下次選人時會覆寫。

**先猜下一步：**回到 `dfs(1, 1)` 後，下一位會試誰？選入後，為何 4 號不能選，而 5 號可以？

**核對：**下一位是 3 號（專長 2），進入 `dfs(2, 3)`：隊伍 `[1, 3]`，`had_tal={2, 3}`，`had_cla=(2, 0)`。4 號仍受第 1 班兩人上限阻擋；5 號（第 2 班、專長 1）合法，進入 `dfs(3, 5)`：隊伍 `[1, 3, 5]`，`had_tal={1, 2, 3}`，`had_cla=(2, 1)`。這是第 2 組，程式輸出 `1 3 5` 後結束。

C++ 版以「選／不選」兩個遞迴分支推進 `pick`，控制流程與上述 Python `for` 迴圈不同，但同樣先探索較小編號的合法隊伍。

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
