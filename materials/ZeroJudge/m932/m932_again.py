
def check(x,y, m, n):
    if (x < 0 or x >= n):
        return False
    if (y < 0 or y >= m):
        return False
    return True




m,n,k = [int(x) for x in input().split()]
map = []
for i in range(m):
    map.append([i for i in input()])

# start positon
y = m-1
x = 0
lst = []
move = [int(x) for x in input().split()]

for mo in move:
    if mo == 0:
        if check(x,y-1, m, n):
            x = x 
            y = y-1
    if mo == 1:
        if check(x+1,y, m, n):
            x = x+1
            y = y
    if mo == 2:
        if check(x+1,y+1, m, n):
            x = x+1
            y = y+1
    if mo == 3:
        if check(x,y+1, m, n):
            x = x
            y = y+1
    if mo == 4:
        if check(x-1,y, m, n):
            x = x-1
            y = y
    if mo == 5:
        if check(x-1,y-1, m, n):
            x = x-1
            y = y-1
    print(map[y][x], end="")
    lst.append(map[y][x])

print('\n',len(list(set(lst))),sep="")