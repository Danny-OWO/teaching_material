r, c, g = [int(x) for x in input().split()]
lst = []
for i in range(r):
    x = input()
    lst.append(x)

pos_r = r-1
pos_c = 0

delta_r = [1,0,-1,-1,0,1]
delta_c = [0,1,1,0,-1,-1]
words = []
moves = [int(x) for x in input().split()]
for i in range(g):
    move = moves[i]
    new_pos_r = pos_r - delta_r[move]
    new_pos_c = pos_c + delta_c[move]

    if -1 < new_pos_r < r and -1 < new_pos_c < c:
        words.append(lst[new_pos_r][new_pos_c])
        pos_r = new_pos_r
        pos_c = new_pos_c
    else:
        words.append(lst[pos_r][pos_c])

print("".join(words))
print(len(list(set(words))))