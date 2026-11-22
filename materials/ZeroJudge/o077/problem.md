---
title: "o077. 菱形範圍加值"
source: ZeroJudge
problemId: o077
difficulty: easy
topics: [matrix, simulation, geometry]
patterns: [range-effect-simulation]
techniques: [bounded-square-scan, boundary-check]
---

對每次操作枚舉中心周圍的正方形，只更新位於矩陣內且與中心的曼哈頓距離不超過 `t` 的格子，最後輸出累加結果。
