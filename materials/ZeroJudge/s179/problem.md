---
title: "s179. 1－比例分割"
source: ZeroJudge
problemId: s179
difficulty: medium
order: 19
topics: [array, prefix-sum, binary-search]
patterns: [first-true, ratio-threshold-query]
techniques: [range-sum-query, integer-cross-multiplication, lower-bound]
prerequisites: [prefix-sum, binary-search]
pitfalls: [floating-point-comparison, off-by-one, linear-scan, integer-overflow]
complexity: {time: "O(n + m log n)", space: "O(n)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=s179)

對每筆詢問 `(l, r, a, b)`，要找唯一的分割點 `k`，使左側在加入 `w[k]` 前還沒達到目標比例，加入後才第一次達到：

$$
\frac{S(l,k-1)}{S(l,r)} < \frac{a}{a+b}
\leq \frac{S(l,k)}{S(l,r)}.
$$

換句話說，答案就是讓累積重量跨過 $\frac{a}{a+b}$ 的**第一個位置**。

## 為什麼需要前綴和

令 `prefix[i]` 表示前 `i` 個元素的總和，並令 `prefix[0] = 0`。任何區間和都能用兩個前綴相減：

$$
S(l,r)=prefix[r]-prefix[l-1].
$$

二分搜尋會反覆檢查不同的 `mid`。若每次都從 `l` 加到 `mid`，一次詢問仍可能退化成線性時間；前綴和讓每次判斷固定只做一次相減，成為 $O(1)$。

## 為什麼可以二分搜尋

固定一筆詢問，定義：

$$
ok(k) \iff S(l,k)\cdot(a+b) \geq a\cdot S(l,r).
$$

因為每個 `w[i]` 都是正整數，`S(l,k)` 隨著 `k` 嚴格遞增，所以 `ok(k)` 只會長成：

```text
false false false ... true true true
```

答案正是第一個 `true`，可以用 lower bound 型二分搜尋。程式以交叉相乘比較整數，沒有必要除法；若改用浮點數比較比例，只是在邀請精度誤差來攪局。

## 動畫：前綴和如何餵給二分搜尋

範例使用 `w = [2, 2, 6, 3, 1, 5]` 與詢問 `(l,r,a,b) = (1,6,1,3)`。播放動畫或逐步前進，觀察區間和如何由前綴相減取得，以及搜尋範圍如何每次砍半。

<div class="algorithm-visualizer" data-ratio-split data-values="2,2,6,3,1,5" data-l="1" data-r="6" data-a="1" data-b="3">
  <div class="visualizer-header">
    <strong>比例分割：prefix + first true</strong>
    <span data-ratio-status>準備建立 prefix</span>
  </div>
  <div class="visualizer-cells" data-ratio-cells></div>
  <p class="visualizer-message" data-ratio-message></p>
  <div class="visualizer-controls">
    <button type="button" data-ratio-next>下一步</button>
    <button type="button" data-ratio-play>播放動畫</button>
    <button type="button" data-ratio-reset>重設</button>
  </div>
</div>

## 二分搜尋不變量

搜尋區間 `[left, right]` 始終包含答案。令 `mid = (left + right) // 2`：

- 若 `ok(mid)` 為真，`mid` 可能就是第一個可行位置，因此保留它並令 `right = mid`。
- 若 `ok(mid)` 為假，答案必定在右邊，因此令 `left = mid + 1`。

當 `left == right`，唯一留下的位置就是答案。注意真分支不是 `right = mid - 1`；那樣可能親手刪掉答案。

## 正確性

前綴和公式讓程式正確取得 $S(l,k)$ 與 $S(l,r)$。正權重使 `ok(k)` 單調，且 `ok(r)` 必為真，因此第一個為真的位置存在。二分搜尋每一步都保留這個位置並縮小搜尋區間，最後停在唯一的第一個 `true`，也就是同時滿足題目左右兩條不等式的分割點。

## 常見錯誤

- 有前綴和卻仍逐一掃描 `k`：每次區間和是 $O(1)$，但整筆詢問仍是 $O(n)$，只會拿到部分分數。
- 寫成 `prefix[r] - prefix[l]`：一基底區間 `[l,r]` 對應的是 `prefix[r] - prefix[l-1]`。
- 只檢查加入 `w[k]` 後達標，卻沒有找「第一個」達標位置；lower bound 型二分搜尋已隱含保證前一格未達標。
- 使用浮點除法比較比例。交叉相乘更精確，也更直接。
- 在 C++ 用 `int` 儲存前綴和或乘積；依限制可能溢位，應使用 `long long`。

## 複雜度

建立前綴和需要 $O(n)$ 時間與 $O(n)$ 空間；每筆詢問二分搜尋需要 $O(\log n)$，總時間為 $O(n+m\log n)$。
