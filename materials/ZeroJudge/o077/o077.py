h,w,n = [int(x) for x in input().split()]

graph = [[0 for i in range(w)] for j in range(h)]





for _ in range(n):
    r,c,t,x = [int(y) for y in input().split()]
    for i in range(r-t,r+t+1,1):
        for j in range(c-t, c+t+1, 1):
            if (not(i < 0 or i >= h or j < 0 or j >= w)):
                if (abs(i - r) + abs(j-c) <= t):
                    graph[i][j] += x




for i in range(h):
    print(*graph[i])
