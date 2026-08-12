import sys

input_data = sys.stdin.read().split()

n = int(input_data[0])
m = int(input_data[1])
r = int(input_data[2])
k = int(input_data[3])
t = int(input_data[4])

talent = list(map(int, input_data[5:]))

ans = 0

had_tal = [0] * (n + 1)
had_cla = [0] * (m + 1)
choosed = [0] * k


def dfs(depth, start):
    global ans

    if depth == k:
        ans += 1
        if ans == t:
            print(*choosed)
            exit()
        return

    # 剩下的人不夠填滿答案
    if depth + (m * r - start) < k:
        return

    for i in range(start, m * r):

        t_t = talent[i]
        t_c = i // r + 1

        if had_tal[t_t]:
            continue

        if had_cla[t_c] == 2:
            continue

        choosed[depth] = i + 1
        had_tal[t_t] = 1
        had_cla[t_c] += 1

        dfs(depth + 1, i + 1)

        had_tal[t_t] = 0
        had_cla[t_c] -= 1


dfs(0, 0)