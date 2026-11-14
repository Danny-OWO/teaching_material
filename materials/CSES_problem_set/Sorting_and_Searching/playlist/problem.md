---
title: Playlist
difficulty: medium
source: CSES
problemId: Playlist
order: 111
topics: [sliding-window, map, array]
patterns: [longest-unique-window]
techniques: [linear-scan]
---

以最後出現位置維護沒有重複歌曲的最長滑動視窗。

!!! note "版本狀態"
    `p_by_gemini.cpp` 會用 `max` 保證左界不倒退；`p.cpp` 少了這個關鍵保護。
