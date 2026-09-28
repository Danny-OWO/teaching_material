---
title: "1894. Find the Student that Will Replace the Chalk"
source: LeetCode
problemId: 1894
difficulty: medium
order: 2
topics: [array, simulation, math]
patterns: [cycle-reduction, repeated-process]
techniques: [modular-arithmetic, linear-scan]
prerequisites: [array, modulo]
pitfalls: [strictly-less, modulo-zero, integer-overflow]
complexity:
  time: "O(n)"
  space: "O(1)"
---

學生依序消耗粉筆；走完最後一位後回到第 0 位。找出第一個面對剩餘粉筆不足的學生。

## 你的解法骨架

```text
計算完整一輪耗量 turn
→ k %= turn，直接跳過所有完整輪
→ 從第 0 位重新模擬剩餘的一小段
```

這是一個很典型的 **cycle reduction**：與其忠實模擬數十億枝粉筆，不如先把重複且不影響相對狀態的完整週期一次消掉。

## 互動圖解

範例 `chalk = [5, 1, 5]`、`k = 22`。完整一輪消耗 11，所以兩輪可以直接用取模消掉。

<div class="algorithm-visualizer" data-chalk-cycle data-values="5,1,5" data-chalk="22">
  <div class="visualizer-header">
    <strong>粉筆週期消除</strong>
    <span data-chalk-step>尚未取模</span>
  </div>
  <div class="visualizer-cells" data-chalk-cells></div>
  <p class="visualizer-message" data-chalk-message></p>
  <div class="visualizer-controls">
    <button type="button" data-chalk-next>下一步</button>
    <button type="button" data-chalk-reset>重設</button>
  </div>
</div>

## 核心不變量

執行 `k %= turn` 後，剩餘粉筆必定小於完整一輪的需求量。因此接下來最多掃描一輪，就一定會遇到無法取得足夠粉筆的學生。

## 正確性

每完成一整輪，學生順序會回到第 0 位，狀態只少了 `turn` 枝粉筆。因此移除任意個完整輪不會改變最後負責替換粉筆的學生。取模保留了與原始 `k` 相同的輪內剩餘量，接著按順序扣除即可找到答案。

## 你的程式碼值得注意的地方

- `turn` 使用 `long long` 是正確的。最多 $10^5$ 位學生、每人最多用 $10^5$ 枝，一輪可能到 $10^{10}$。
- 你的寫法先扣除再判斷 `k < 0`，因此額外處理了 `k == 0`，回傳學生 0。邏輯正確，但存在更直接的寫法：先判斷 `if (k < chalk[i]) return i;`，否則再扣除。
- 題目條件是「現有粉筆嚴格少於需求量」才替換。等於需求量時，學生仍能用完粉筆，下一位才替換；這個邊界正是最容易被 `<=` 偷走分數的地方。

## 複雜度

加總一輪需要 $O(n)$，取模是 $O(1)$，最後定位最多再掃一輪，所以總時間 $O(n)$、額外空間 $O(1)$。若你真的逐枝或逐輪模擬，時間則會和 `k` 綁在一起，那不是努力，是把 CPU 當苦力。

