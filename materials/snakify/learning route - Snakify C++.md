# Snakify C++ 基礎課程定位

這套課程以 **C++17** 為準，配合 Snakify 的基礎題目建立語法與程式邏輯。它是一套 C++ 基礎課程，不是 APCS 演算法課程；完成後，再銜接 APCS 學習路線。

週次可以依班級進度調整，重點是維持章節順序。

| 建議週次 | Snakify 章節 | 核心定位 |
|---|---|---|
| 第 1 週 | 第 1 章：輸入、輸出與數字 | Variable、input/output、expression |
| 第 2 週 | 第 2 章：整數與浮點數 | Numeric types、integer division、`cmath` |
| 第 3 週 | 第 3 章：條件判斷 | Condition、comparison、logical operators |
| 第 4 週 | 第 4 章：`for` 迴圈 | Loop、counting、nested loop |
| 第 5 週 | 第 5 章：字串 | Character、string、index、traversal |
| 第 6 週 | 第 6 章：`while` 迴圈 | Unknown repetitions、`break`、`continue` |
| 第 7 週 | 第 7 章：`vector` | Sequence、loop with data、basic algorithms |
| 第 8 週 | 第 8 章：函式與基礎遞迴 | Function、parameter、reference；遞迴只建立基本概念 |
| 第 9 週 | 第 9 章：二維 `vector` | Table、matrix、row and column traversal |
| 第 10 週 | 第 10 章：`set` | Unique values、lookup、ordered set |
| 第 11 週 | 第 11 章：`map` | Key-value、frequency table、dictionary lookup |

## 課程邊界

| 主題 | 本課程定位 |
|---|---|
| Raw array | 不教，基礎題統一使用 `vector` |
| Pointer | 不列入基礎課程；第 8 章只介紹 reference |
| Bit operation | Snakify 基礎題用不到，進入 APCS 後有需要再補 |
| `struct` | 銜接 APCS 或多欄位資料題時補充 |
| File processing | 跳過 |
| Linked list | 不屬於這套基礎課程，也不是初期 APCS 重點 |
| Binary tree | 進入 APCS／資料結構課程後再教 |
| Object-oriented programming | 另立主題，不塞進 Snakify 基礎課程 |
| Preprocessing | 第 1 章只理解 `#include`；不深入 macro |
| Standard library | 不獨立放到最後，透過 `string`、`vector`、`algorithm`、`set`、`map` 分散學習 |

完成第 11 章代表 C++ 基礎階段告一段落。接下來的排序、stack、queue、binary search、DFS、tree、greedy 與 dynamic programming，屬於 [APCS 課程路線（C++）](../APCS/learning route - C++.md)。
