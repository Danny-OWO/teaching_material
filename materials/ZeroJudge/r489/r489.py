r, c = map(int, input().split())

lst = []
pic = []

for i in range(r):
    row = list(map(int, input().split()))
    lst.append(row)

for i in range(r):
    row = list(map(int, input().split()))
    pic.append(row)

situ = [0, 0, 0, 0]

for i in range(r):
    for j in range(c):

        # 0°
        if lst[i][j] == pic[i][j]:
            situ[0] += 1

        # 180°
        if lst[i][j] == pic[r - 1 - i][c - 1 - j]:
            situ[1] += 1

        if r == c:

            # 90°
            if lst[i][j] == pic[r - 1 - j][i]:
                situ[2] += 1

            # 270°
            if lst[i][j] == pic[j][c - 1 - i]:
                situ[3] += 1

ans = max(situ)

print(str(ans * 100 // (r * c)) + "%")