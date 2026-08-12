n = int(input())
lst = [0] + [int(x) for x in input().split()]
dif = []

for i in range(1, n+1):
    dif.append(lst[i] - lst[i-1])

print(*dif)