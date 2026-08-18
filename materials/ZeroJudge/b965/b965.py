r, c, m = [int(x) for x in input().split()]
matrix = []

for i in range(r):
    _ = [int(y) for y in input().split()]
    matrix.append(_)

#print(matrix)

def flip():
    global matrix
    matrix.reverse()
    
def turn():
    global matrix, r, c
    lst = []
    for j in range(c-1, -1, -1):
        _ = []
        #print(456)
        for i in range(0, r, 1):
            _.append(matrix[i][j])
            #print(123)
        lst.append(_)
    #print(lst)
    matrix = lst
    r,c = c,r
    #print(matrix)


moves = [int(o) for o in input().split()]
moves.reverse()

for k in moves:
    if k == 1:
        flip()
    else:
        turn()

print(r,c)
for p in range(r):
    print(*matrix[p])

#print(matrix)
'''
3 2 3
1 1
3 1
1 2
1 0 0
'''