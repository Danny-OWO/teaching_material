r,c,d = [int(x) for x in input().split()]
k = int(input())
dino = [[0] * c for _ in range(r)]
height = [[d] * c for _ in range(r)]

for i in range(k):
    a,b = [int(x) for x in input().split()]
    dino[a][b] += 1

move = int(input())

for j in range(move):
    a,b,l,d = [int(x) for x in input().split()]
    length = int((l-1)/2)
    kill = 0
    for delta1 in range(-length, length+1, 1):
        for delta2 in range(-length, length+1, 1):
            t_x = b + delta1
            t_y = a + delta2

            if 0 <= t_x < c and 0 <= t_y < r:
                if dino[t_y][t_x] != 0:
                    kill += dino[t_y][t_x]
                    dino[t_y][t_x] = 0
    k -= kill
    if kill == 0:
        for delta1 in range(-length, length+1, 1):
            for delta2 in range(-length, length+1, 1):
                t_x = b + delta1
                t_y = a + delta2
                if 0 <= t_x < c and 0 <= t_y < r:
                    height[t_y][t_x] -= d
    
maxx = height[0][0]
minn = height[0][0]

for i in range(r):
    for j in range(c):
        t = height[i][j]
        if t > maxx:
            maxx = t
        if t < minn:
            minn = t

print(maxx, minn, k)