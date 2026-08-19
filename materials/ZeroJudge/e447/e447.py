from collections import deque
n = int(input())
q = deque()
for i in range(n):
    lst = [int(x) for x in input().split()]

    if lst[0] == 1:
        q.append(lst[1])
    elif lst[0] == 2:
        if q:
            print(q[0])
        else:
            print(-1)
    else:
        if q:
            q.popleft()