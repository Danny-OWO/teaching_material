n = int(input())
lst = []
for i in range(n):
    move = [int(x) for x in input().split()]
    choose = move[0]
    if choose == 3:
        lst.append(move[1])
    elif choose == 2:
        print(lst[-1])
    else:
        lst.pop()