k,q,r = [int(x) for x in input().split()]
start = [i for i in input()]
ans = []
for i in range(q):
    temp = ['a' for j in range(k)]
    goal = [int(x) for x in input().split()]
    for p in range(k):
        temp[goal[p]-1] = start[p]
    ans.append(temp)
    start = temp


for l in range(r):
    for ele in ans:
        print(ele[l], end="")
    print()


