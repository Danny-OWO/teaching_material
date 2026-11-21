n, m = [int(x) for x in input().split()]
lst = []
su = 0
for i in range(n):
    nums = [int(x) for x in input().split()]
    maxnum = max(nums)
    lst.append(maxnum)
    su+=maxnum


print(su)
key = 0
for i in range(len(lst)):
    if su % lst[i] == 0:
        if key == 0:
            print(lst[i], end="")
            key = 1
        else:
            print(f" {lst[i]}",end="")
if (not key):
    print(-1)
