#this approach got 40% even we implement prefix
n, m = [int(x) for x in input().split()]
w = [int(x) for x in input().split()]

prefix = []
temp = 0
prefix.append(0)

for i in range(len(w)):
    temp += w[i]
    prefix.append(temp)

def seek():
    l,r,a,b = [int(x) for x in input().split()]
    left = l
    right = r
    while (left <= right):
        k = (left+right)//2
        slk_1 = prefix[k-1] - prefix[l-1]
        s_lr = prefix[r] - prefix[l-1]
        s_lk = prefix[k] - prefix[l-1]
        if (s_lr * a > slk_1 * (a+b)):
            if (s_lk * (a+b) >= a * s_lr):
                left = k+1
                ans = k   
            left = k+1             
        else:
            right = k-1
    print(k)
    return





for i in range(m):
    seek()