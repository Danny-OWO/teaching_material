from bisect import bisect_left, bisect_right


# 想法：
#
# 一般 difference array 的問題是：
#
# 時間最大可以到 10^8，
# 如果真的為每一天開一格 array，
# 記憶體和時間都會很浪費。
#
#
# 但題目真正關心的不是「每一天」，
# 而是：
#
# 「旅行團會出現的那些時間點」
#
#
# 所以我們只保留旅行團的時間。
#
# 例如：
#
# 原本時間：
# 5 7 10
#
# 壓縮後：
# index
# 0 1 2
#
#
# 接下來對每一個表演 [start, end]，
# 我們想知道：
#
# 哪些旅行團的位置會被這個表演覆蓋？
#
#
# left：
# 第一個時間 >= start 的旅行團
#
# right：
# 第一個時間 > end 的旅行團
#
#
# 因此真正被覆蓋的是：
#
# [left, right)
#
#
# 我們就可以在「壓縮後的 index」上做 difference array：
#
# diff[left] += 1
# diff[right] -= 1
#
#
# 最後 prefix sum：
#
# diff[i]
#
# 就代表第 i 個旅行團可以看到幾場表演。


n, m = map(int, input().split())

tour = list(map(int, input().split()))

# coordinate compression 最重要的一步：
# 先把真正會被詢問的時間排序
tour.sort()


# 多開一格，因為 right 有可能 == n
diff = [0] * (n + 1)


for _ in range(m):
    start, end = map(int, input().split())

    # 第一個 >= start 的位置
    left = bisect_left(tour, start)

    # 第一個 > end 的位置
    right = bisect_right(tour, end)

    # 如果有旅行團落在這個範圍內
    #
    # 例如：
    #
    # tour = [2, 5, 7, 10, 13]
    #
    # 表演 [5, 10]
    #
    # left  = 1
    # right = 4
    #
    # 被影響的是 index：
    #
    # 1, 2, 3
    #
    # 也就是：
    #
    # 5, 7, 10

    diff[left] += 1
    diff[right] -= 1


# prefix sum
#
# 把：
#
# 「從這裡開始 +1 / 從這裡開始 -1」
#
# 還原成：
#
# 「每個旅行團總共能看到幾場」
for i in range(1, n):
    diff[i] += diff[i - 1]


# 每個旅行團看到的表演數加起來
ans = 0

for i in range(n):
    ans += diff[i]

print(ans)