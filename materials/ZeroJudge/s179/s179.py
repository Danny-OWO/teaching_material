n, m = [int(x) for x in input().split()]
w = [int(x) for x in input().split()]

prefix = []
temp = 0
prefix.append(0)

for i in range(len(w)):
    temp += w[i]
    prefix.append(temp)

for i in range(m):
    l,r,a,b = [int(x) for x in input().split()]
