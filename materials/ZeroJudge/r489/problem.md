---
title: "r489. 2－航空拍照圖"
source: ZeroJudge
problemId: r489
difficulty: medium
order: 11
topics: [matrix, geometry, simulation]
patterns: [enumerate-transformations]
techniques: [coordinate-transform, rotation]
prerequisites: [matrix-indexing]
pitfalls: [non-square-rotation, coordinate-formula, integer-percentage]
complexity: {time: "O(rc)", space: "O(rc)"}
---

[ZeroJudge 題目](https://zerojudge.tw/ShowProblem?problemid=r489)

比較兩張航拍圖，在允許旋轉的情況下找出最高相似比例。旋轉只有 0、90、180、270 度四種，狀態很少，全部檢查比設計複雜最佳化更可靠。

## 解法

對每個原圖座標 `(i,j)`，分別映射到各旋轉角度在另一張圖的座標並計算相同格數。非方陣旋轉 90 或 270 度後尺寸互換，若題目要求同尺寸疊合，就只能比較尺寸一致的角度。

## 座標公式

- 0°：`(i, j)`
- 180°：`(r-1-i, c-1-j)`
- 方陣 90°／270°：依旋轉方向使用 `(r-1-j, i)` 或 `(j, c-1-i)`

## 常見錯誤

- row 與 column 在公式裡互換錯誤。
- 長方形也直接套方陣 90° 公式比較。
- 先做整數除法再乘 100，讓所有不足 100% 的答案變 0。
- 同時旋轉兩張圖枚舉 16 組；其實固定一張、旋轉另一張就涵蓋相對角度。

## 複雜度

四種角度各掃一次，仍是 $O(rc)$；若直接建立旋轉矩陣則需 $O(rc)$ 額外空間。

