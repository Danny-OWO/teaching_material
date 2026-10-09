# 想法：
# 如果我們想知道「每一天有幾個表演可以看」，
# 最直覺的方法是：
#
# 對每一個表演 [start, end]，
# 把 start 到 end 的每一天全部 +1。
#
# 例如：
# 表演 [2, 5]
#
# time:
# day     1 2 3 4 5 6
#         0 1 1 1 1 0
#
# 但是如果直接：
#
# for i in range(start, end + 1):
#     time[i] += 1
#
# 一個表演可能就要修改很多格。
#
# 我們可以換個想法：
#
# [2, 5] 代表：
#
# 從第 2 天開始，表演數量 +1
# 到第 6 天開始，這個表演消失，所以 -1
#
# 所以只需要：
#
# diff[2] += 1
# diff[6] -= 1
#
# 最後再做 prefix sum，
# 就可以把「變化量」還原成每一天真正有幾個表演。
#
# 這就是 difference array。


n, m = map(int, input().split())

tour = list(map(int, input().split()))

MAX_TIME = 100000000

diff = [0] * (MAX_TIME + 2)

for _ in range(m):
    start, end = map(int, input().split())

    diff[start] += 1
    diff[end + 1] -= 1


# prefix sum
# 把 difference array 還原成：
# 每一天到底有幾個表演
for i in range(1, MAX_TIME + 1):
    diff[i] += diff[i - 1]


ans = 0

for t in tour:
    ans += diff[t]

print(ans)