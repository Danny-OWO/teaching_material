n, m = [int(x) for x in input().split()]
w = [int(x) for x in input().split()]

prefix = [0]
temp = 0

for i in range(len(w)):
    temp += w[i]
    prefix.append(temp)


def seek():
    l, r, a, b = [int(x) for x in input().split()]

    s_lr = prefix[r] - prefix[l-1]

    left = l
    right = r

    while left < right:
        mid = (left + right) // 2

        s_lmid = prefix[mid] - prefix[l-1]

        if s_lmid * (a+b) >= a * s_lr:
            right = mid
        else:
            left = mid + 1

    print(left)


for i in range(m):
    seek()