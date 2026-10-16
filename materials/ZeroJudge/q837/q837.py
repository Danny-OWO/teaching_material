m,n,k = [int(x) for x in input().split()]
words = []
for i in range(m):
    words.append(input())

prev = [0 for i in range(m)]

def start(m,n,k):
    global prev
    spin = [-(int(x)) for x in input().split()]
    for t in range(m):
        spin[t]+=prev[t]
        spin[t] %= n
    score = 0
    for j in range(n):
        lst = []
        for k in range(m):
            lst.append(words[k][spin[k]])
            spin[k]+=1
            if spin[k] == n:
                spin[k] = 0

        
        temp = list(set(lst))
        local_score = lst.count(temp[0])
        for i in temp:
            x = lst.count(i) 
            if x > local_score:
                local_score = x
        score += local_score



    prev = spin
    return score


ans = 0
for i in range(k):
    ans += start(m,n,k)

print(ans)    