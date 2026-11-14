# if 0 will be continuous
n = int(input())
k = [float('inf')]
for x in input().split():
    k.append(int(x))
k.append(float('inf'))


left = 0
right = 0
ans = 0
count = 0

while (left <= right and left < n+1 and right < n+1):
    right += 1
    #print(right)
    if (k[right] != 0 and count == 0):
        left = right
    elif (k[right] == 0):
        count+=1
    else:
        ans += count * min(k[left], k[right])
        count = 0
        left = right
        #print(ans)

print(ans)







'''

float('inf')                                                                        float('inf') 
             0 0 0 2 0 3 0 4 5 2 3 0 0 0 0 1 0


'''