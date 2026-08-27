from collections import deque

n, k = map(int, input().split())

container = list(map(int, input().split()))

pre = [0]
s = 0

for i in range(n):
    s += container[i]
    pre.append(s)

dq = deque()
dq.append(0)

max_score = 0

for r in range(1, n + 1):

    # 太久以前的 index 丟掉
    while dq and r - dq[0] > k:
        dq.popleft()

    # dq[0] 是目前合法範圍中最小的 pre
    max_score = max(max_score, pre[r] - pre[dq[0]])

    # 維護 pre[dq] 單調遞增
    while dq and pre[r] <= pre[dq[-1]]:
        dq.pop()

    dq.append(r)

print(max_score)