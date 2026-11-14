n = int(input())
k = [int(x) for x in input().split()]
ans = 0
for j in range(n):
    if (j == 0 and k[j] == 0):
        ans+=k[1]
    elif (j == n-1 and k[j] == 0):
        ans+=k[j-1]
    else:
        if (k[j] == 0):
            ans+=min(k[j-1], k[j+1])

print(ans)