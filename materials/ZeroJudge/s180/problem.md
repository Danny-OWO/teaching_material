---
title: "s180. 2－觀光旅遊"
source: ZeroJudge
problemId: s180
difficulty: medium
order: 20
topics: [array, difference-array, coordinate-compression, binary-search]
patterns: [range-addition, count-points-in-interval]
techniques: [prefix-sum, bisect-left, bisect-right]
prerequisites: [array, sorting, binary-search]
pitfalls: [quadratic-enumeration, large-date-range, inclusive-endpoint, duplicate-arrivals]
complexity: {time: "O(n log n + m log n)", space: "O(n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=s180)

第 `i` 個旅行團在第 `t_i` 天抵達；第 `j` 個表演從第 `s_j` 天演到第 `e_j` 天，包含首尾。只要 $s_j \le t_i \le e_j$，這組旅行團與表演就貢獻一場。答案是所有合法配對的數量。

這個目錄保留四份原有 Python 解法。它們由逐一檢查、日期差分，逐步改進到只處理旅行團抵達日期的高效做法。

## `s180.py`：逐一檢查（40 分版本）

對每個表演 `[start, end]`，逐一檢查所有旅行團的抵達日期是否落在區間內。這個想法直接對應題意，適合當作正確性的基準。

每個表演要檢查 `n` 團，總時間 $O(nm)$。當 `n`、`m` 都達 $10^5$，最多要檢查 $10^{10}$ 個配對，因此這份程式只能通過較小的測資。

## `s180-1.py`：對日期做差分

如果要知道「每一天有幾個表演」，直接對每個 `[start, end]` 的每一天加一，可能需要修改很多格。差分陣列只記錄表演數量發生變化的位置：

```text
diff[start] += 1
diff[end + 1] -= 1
```

例如表演 `[2, 5]` 在第 2 天開始，從第 6 天起消失。因此第 2 天記 `+1`，第 6 天記 `-1`。對 `diff` 做前綴和後，`diff[t]` 就是第 `t` 天的表演數；把每個旅行團抵達日的數值加起來即為答案。

這個版本把日期範圍開到 $10^8$。雖然時間與空間是 $O(m+n+U)$（$U$ 為最大日期），Python 中一億格陣列需要大量記憶體，超過題目 256 MB 限制，也需要掃過所有日期，因此**無法用於完整測資**。它主要用來理解差分的原理。

## `s180-2.py`：只在旅行團日期上做差分

題目只會詢問旅行團抵達的日期，不需要儲存其他日子的表演數。先將 `tour` 排序；排序後第 `i` 格代表一個旅行團，即使多團同一天到達也保留多格。

對每個表演 `[start, end]`，用二分搜尋找出：

- `left = bisect_left(tour, start)`：第一個日期 **大於等於** `start` 的索引。
- `right = bisect_right(tour, end)`：第一個日期 **大於** `end` 的索引。

能看這場表演的旅行團恰好位於半開區間 `[left, right)`。在排序後的旅行團索引上做差分：

```text
diff[left] += 1
diff[right] -= 1
```

`diff` 要開 `n + 1` 格，因為 `right` 可能等於 `n`。最後對前 `n` 格做前綴和，`diff[i]` 就是第 `i` 個旅行團能看的表演數，再把它們加總。

例如 `tour = [2, 5, 7, 10, 13]`，表演 `[5, 10]` 得到 `left = 1`、`right = 4`，因此索引 1、2、3 的旅行團各增加一場。

排序花 $O(n\log n)$；每個表演做兩次二分搜尋，花 $O(m\log n)$；前綴和與加總花 $O(n)$。總時間 $O(n\log n+m\log n)$，額外空間 $O(n)$。

## `s180-3.py`：直接計算區間內的人數

沿用排序與同樣的兩個邊界，但若只需要所有旅行團的總場次，其實不用建立差分陣列。一場表演的貢獻就是：

$$
\operatorname{bisect\_right}(tour,end)
-\operatorname{bisect\_left}(tour,start).
$$

以上例而言，`right - left = 4 - 1 = 3`，對應抵達日期 `5`、`7`、`10`。每個表演的貢獻直接加到答案。時間同為 $O(n\log n+m\log n)$，排序後不需額外的差分陣列。

## 為什麼二分搜尋版本正確

排序後，所有滿足 $start \le t_i \le end$ 的抵達日期連續排列。`left` 之前的日期都小於 `start`，`right` 起的日期都大於 `end`，所以 `[left, right)` 恰好包含能看該表演的所有旅行團。`s180-2.py` 為這些旅行團各加一場；`s180-3.py` 直接把人數 `right - left` 加到總和，兩者都將每個合法配對計算一次。

## 常見錯誤

- 忘記先排序 `tour` 就呼叫 `bisect`。
- 用 `bisect_left(tour, end)` 當右界，漏算結束當天抵達的旅行團。
- 用 `bisect_right(tour, start)` 當左界，漏算開始當天抵達的旅行團。
- 將相同的抵達日期去重；不同旅行團仍須各計一場。
- 對日期範圍直接配置一億格陣列，造成記憶體不足。
