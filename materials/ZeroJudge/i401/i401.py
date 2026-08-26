import bisect

n = int(input())

x_based = [[] for _ in range(30001)]
y_based = [[] for _ in range(60001)]

for _ in range(n):
    xx, yy, tt = map(int, input().split())
    x_based[xx].append([yy, tt])
    y_based[yy + 30000].append([xx, tt])

for v in x_based:
    v.sort()

for v in y_based:
    v.sort()

ans = 0

x = 0
y = 0
face = 'r'

while True:

    if face == 'r':
        v = y_based[y + 30000]
        ub = bisect.bisect_right(v, [x, 1])

        if ub == len(v):
            print(ans)
            break

        x = v[ub][0]
        typ = v[ub][1]

        ans += 1

        if typ == 1:
            face = 'd'
        else:
            face = 'u'


    elif face == 'l':
        v = y_based[y + 30000]
        lb = bisect.bisect_left(v, [x, 0])

        if lb == 0:
            print(ans)
            break

        lb -= 1

        x = v[lb][0]
        typ = v[lb][1]

        ans += 1

        if typ == 1:
            face = 'u'
        else:
            face = 'd'


    elif face == 'u':
        v = x_based[x]
        ub = bisect.bisect_right(v, [y, 1])

        if ub == len(v):
            print(ans)
            break

        y = v[ub][0]
        typ = v[ub][1]

        ans += 1

        if typ == 1:
            face = 'l'
        else:
            face = 'r'


    elif face == 'd':
        v = x_based[x]
        lb = bisect.bisect_left(v, [y, 0])

        if lb == 0:
            print(ans)
            break

        lb -= 1

        y = v[lb][0]
        typ = v[lb][1]

        ans += 1

        if typ == 1:
            face = 'r'
        else:
            face = 'l'