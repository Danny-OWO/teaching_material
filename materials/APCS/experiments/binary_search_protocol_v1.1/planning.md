# Binary Search Teaching Material — Planning Record

## Stage 0 — Teaching Material Specification

- Topic: 二分搜尋。
- Target audience: 準備 APCS 的高中生，已會變數、條件、迴圈、函式、陣列與索引。
- Intended outcomes: 判斷適用條件、追蹤搜尋範圍、正確實作、解釋複雜度、處理邊界搜尋並使用 C++ / Python 工具。
- Scope: 精確值搜尋、閉區間不變量、找不到、邊界更新、重複值、lower/upper bound、複雜度與練習。
- Exclusions: 二分答案、浮點二分、自訂 comparator、二元搜尋樹僅作概念區隔。
- Languages: 語言無關概念、C++、Python。
- Style: 沿用電話簿、Sam 與高松燈故事；幽默不得犧牲概念精確度。
- Reference: `materials/APCS/binary_search.md`。
- Output: 新增獨立 Markdown，不覆寫基準稿。
- User approval: 2026-11-13；使用者確認沿用故事。

## Stage 1 — Learning Objectives

| ID | Ability | Prerequisite | Observable evidence |
|---|---|---|---|
| LO1 | 判斷能否二分 | 排序、比較 | 能反駁未排序反例 |
| LO2 | 追蹤閉區間搜尋 | 索引、整數除法 | 正確列出每輪 L/M/R |
| LO3 | 實作精確搜尋 | 迴圈、函式 | 通過空陣列、首尾、缺失值測試 |
| LO4 | 解釋對數複雜度 | 指數與對數直覺 | 從每輪折半推導輪數 |
| LO5 | 處理重複值邊界 | LO2、LO3 | 區分 exact/lower/upper bound |
| LO6 | 使用標準工具 | iterator / Python list | 安全處理 `end()`、`len(a)` |
| LO7 | 選擇搜尋策略 | 基本複雜度 | 比較一次與多次查詢成本 |

## Stage 2 — Knowledge Architecture

```text
有序資料與索引
  -> 搜尋區間與不變量
  -> 中點比較與安全排除
  -> 邊界更新與終止
  -> 精確搜尋
  -> lower / upper bound
  -> 重複值計數與語言工具
```

### Coverage Matrix

- Required: 有序前提、閉區間、不變量、三種比較、`middle ± 1`、終止、缺失值、複雜度、邊界安全。
- Recommended: lower/upper bound、重複值、極端案例、閉區間與半開區間不可混用。
- Optional and excluded from formal teaching: 二分答案、浮點二分、自訂 comparator / key。

### External verification

- Python documentation: <https://docs.python.org/3/library/bisect.html>
- C++ working draft, binary search algorithms: <https://eel.is/c++draft/alg.binary.search>
- MIT OpenCourseWare, binary search and logarithmic growth: <https://ocw.mit.edu/courses/6-00sc-introduction-to-computer-science-and-programming-spring-2011/68250e56c0eabd1149fb4b0084ffa3d5_GmkRmETGghw.pdf>

## Stage 3 — Instructional Blueprint

1. Story and motivation — LO1, LO4 — compare linear and binary search.
2. Analogy mapping and failure boundary — LO1 — map phone book operations to array invariants.
3. Closed interval and tracing — LO2 — worked example followed by retrieval check.
4. Exact-search implementation — LO3 — pseudocode, C++, Python.
5. Edge-case attack table — LO3 — empty, one element, endpoints and absence.
6. Complexity derivation — LO4 — repeated halving, not single-run timing.
7. Boundary search — LO5 — partition diagrams and duplicate counting.
8. Standard tools — LO6 — safe end-position checks.
9. Error clinic — LO1–LO6 — counterexamples and debugging.
10. Transfer exercises — LO7 — decide whether preprocessing is worthwhile.

Planning approval received from the user on 2026-11-13.
