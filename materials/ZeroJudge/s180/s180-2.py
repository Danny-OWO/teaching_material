from bisect import bisect_left, bisect_right

n, m = map(int, input().split())

tour = list(map(int, input().split()))

tour.sort()

diff = [0] * (n + 1)

for _ in range(m):
    start, end = map(int, input().split())

    left = bisect_left(tour, start)

    right = bisect_right(tour, end)

    diff[left] += 1
    diff[right] -= 1

for i in range(1, n):
    diff[i] += diff[i - 1]

ans = 0

for i in range(n):
    ans += diff[i]

print(ans)
