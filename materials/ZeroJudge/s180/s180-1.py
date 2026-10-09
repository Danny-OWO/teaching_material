n, m = map(int, input().split())

tour = list(map(int, input().split()))

MAX_TIME = 100000000

diff = [0] * (MAX_TIME + 2)

for _ in range(m):
    start, end = map(int, input().split())

    diff[start] += 1
    diff[end + 1] -= 1

for i in range(1, MAX_TIME + 1):
    diff[i] += diff[i - 1]

ans = 0

for t in tour:
    ans += diff[t]

print(ans)
