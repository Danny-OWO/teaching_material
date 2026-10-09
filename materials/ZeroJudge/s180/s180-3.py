from bisect import bisect_left, bisect_right


# 想法：
#
# 對每一個表演 [start, end]，
# 我們想知道：
#
# 有多少旅行團的到達時間 t 滿足
#
# start <= t <= end
#
#
# 如果旅行團時間沒有排序，
# 我們只能一個一個掃描，會變成 O(nm)。
#
# 但如果先把旅行團時間排序：
#
# tour = [2, 5, 7, 10, 13]
#
# 假設現在有一個表演：
#
# [5, 10]
#
# 我們其實只需要找到兩個位置：
#
# left：
# 第一個 >= 5 的位置
#
# right：
# 第一個 > 10 的位置
#
#
# index    0   1   2   3   4
# tour     2   5   7  10  13
#              ↑           ↑
#            left        right
#
#
# left = 1
# right = 4
#
# 所以落在 [5, 10] 裡面的旅行團數量：
#
# right - left
# = 4 - 1
# = 3
#
# 對應：
#
# 5, 7, 10
#
#
# Python 中：
#
# bisect_left(tour, start)
#     → 第一個 >= start 的位置
#
# bisect_right(tour, end)
#     → 第一個 > end 的位置
#
# 因此每個表演的答案就是：
#
# right - left


n, m = map(int, input().split())

tour = list(map(int, input().split()))

# binary search 前一定要先排序
tour.sort()

ans = 0


for _ in range(m):
    start, end = map(int, input().split())

    # 找第一個 >= start 的位置
    left = bisect_left(tour, start)

    # 找第一個 > end 的位置
    right = bisect_right(tour, end)

    # [left, right) 中有多少個旅行團
    ans += right - left


print(ans)