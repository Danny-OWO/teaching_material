from bisect import bisect_left, bisect_right

n, m = map(int, input().split())

tour = list(map(int, input().split()))

tour.sort()

ans = 0

for _ in range(m):
    start, end = map(int, input().split())

    left = bisect_left(tour, start)

    right = bisect_right(tour, end)

    ans += right - left

print(ans)
