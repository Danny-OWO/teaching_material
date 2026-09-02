n = int(input())
apples = [int(x) for x in input().split()]
ans = float('inf')
sum = sum(apples)

def dfs(depth, s):
    global ans
    if depth == n:
        ans = min(ans, abs(s * 2 - sum))
        return

    dfs(depth + 1, s)
    dfs(depth + 1, s + apples[depth])

dfs(0,0)

print(ans)