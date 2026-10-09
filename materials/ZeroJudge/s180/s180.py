# this method is dumb and um but it work
# cuz this approach is too slow you will only get 40%

n,m = [int(x) for x in input().split()]
approach = [int(x) for x in input().split()]
ans = 0
for i in range(m):
    lst = [int(x) for x in input().split()]
    for j in range(n):
        if lst[0] <= approach[j] <= lst[1]:
            ans+=1

print(ans)