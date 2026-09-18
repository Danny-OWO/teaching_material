nums = []


def printlst(x):
    seen = set()

    for lst in x:
        key = tuple(lst)

        if key not in seen:
            seen.add(key)
            print("+".join(map(str, lst)))


def dfs(n, t, s, index, lst, x):
    if s == n:
        x.append(lst.copy())
        return

    if index == t or s > n:
        return

    # 選
    lst.append(nums[index])
    dfs(n, t, s + nums[index], index + 1, lst, x)
    lst.pop()

    # 不選
    dfs(n, t, s, index + 1, lst, x)


while True:
    lst = [int(v) for v in input().split()]
    n = lst[0]
    t = lst[1]

    if n == 0 and t == 0:
        break

    nums = lst[2:]
    x = []

    print(f"Sum of {n}:")
    dfs(n, t, 0, 0, [], x)
    printlst(x)