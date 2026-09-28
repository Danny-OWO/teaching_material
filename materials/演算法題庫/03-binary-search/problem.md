---
title: "704. Binary Search｜二分搜尋"
source: LeetCode
problemId: 704
difficulty: easy
order: 3
topics: [array, binary-search]
patterns: [monotonic-search-space, interval-invariant]
techniques: [closed-interval]
prerequisites: [sorted-array, loop-invariant]
pitfalls: [off-by-one, wrong-bound-update, midpoint-overflow]
complexity:
  time: "O(log n)"
  space: "O(1)"
---

在遞增排序陣列中尋找 `target`；存在就回傳索引，否則回傳 `-1`。

## 辨識線索

不是「看到陣列就二分」，而是搜尋空間有單調結構：比較 `nums[mid]` 與 `target` 後，可以證明至少一半不可能包含答案。

## 互動動畫

下面採用閉區間 `[left, right]`。注意每次更新都必須真正排除 `mid`，否則可能原地踏步到宇宙熱寂。

<div class="algorithm-visualizer" data-binary-search data-values="1,3,5,7,9,11,13" data-target="11">
  <div class="visualizer-header">
    <strong>搜尋 target = 11</strong>
    <span data-visualizer-step>Step 0</span>
  </div>
  <div class="visualizer-cells" data-visualizer-cells></div>
  <p class="visualizer-message" data-visualizer-message></p>
  <div class="visualizer-controls">
    <button type="button" data-visualizer-next>下一步</button>
    <button type="button" data-visualizer-play>自動播放</button>
    <button type="button" data-visualizer-reset>重設</button>
  </div>
</div>

## 核心不變量

每次迴圈開始時：若 `target` 存在，它一定在閉區間 `[left, right]` 中。

- `nums[mid] < target`：`mid` 與左側都太小，令 `left = mid + 1`。
- `nums[mid] > target`：`mid` 與右側都太大，令 `right = mid - 1`。
- 相等：回傳 `mid`。

## 正確性與終止

初始化時 `[0, n - 1]` 包含所有可能位置。每次比較只刪除經排序性證明不可能含答案的部分，因此不變量保持成立。每輪至少排除 `mid`，區間嚴格縮小；最後找到答案，或得到 `left > right` 的空區間。

## 常見錯誤

- 閉區間卻寫成 `while (left < right)`，漏掉最後一格。
- 更新為 `left = mid` 或 `right = mid`，區間可能不再縮小。
- 寫 `(left + right) / 2`；在一般整數環境可能溢位，使用 `left + (right - left) / 2`。

## 延伸思考

「找某個值」只是入門版。更通用的能力是找第一個滿足條件的位置，也就是 lower bound。

