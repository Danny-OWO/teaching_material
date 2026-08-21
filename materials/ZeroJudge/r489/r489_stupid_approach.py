def rotate90(a):
    r = len(a)
    c = len(a[0])

    result = [[0] * r for _ in range(c)]

    for i in range(r):
        for j in range(c):
            result[j][r - 1 - i] = a[i][j]

    return result


def compare(a, b):
    # 尺寸不一樣，不能直接比較
    if len(a) != len(b):
        return -1

    if len(a[0]) != len(b[0]):
        return -1

    same = 0

    for i in range(len(a)):
        for j in range(len(a[0])):
            if a[i][j] == b[i][j]:
                same += 1

    return same


r, c = map(int, input().split())

lst = []
pic = []

for i in range(r):
    lst.append(list(map(int, input().split())))

for i in range(r):
    pic.append(list(map(int, input().split())))


# 儲存四種旋轉
lst_rotate = [lst]
pic_rotate = [pic]

# 每次把上一張再轉 90°
for i in range(1, 4):
    lst_rotate.append(rotate90(lst_rotate[i - 1]))
    pic_rotate.append(rotate90(pic_rotate[i - 1]))


best = 0

# 4 × 4 = 16 種組合全部試
for a in range(4):
    for b in range(4):
        same = compare(lst_rotate[a], pic_rotate[b])

        if same != -1:
            best = max(best, same)


print(str(best * 100 // (r * c)) + "%")