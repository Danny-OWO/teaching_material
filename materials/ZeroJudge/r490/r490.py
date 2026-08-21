n = int(input())
lst = [0 for i in range(1001)]

for i in range(n):
    x = input()
    place = int(x[:3:])
    sodd = 0
    seven = 0
    for i in range(0, 12, 2):
        sodd += int(x[i])
        seven += int(x[i+1])

    if ((sodd + 3 * seven) % 10 + int(x[-1]) == 0 or (sodd + 3 * seven) % 10 + int(x[-1]) == 10):
        lst[place] += 1

tag = 0
amount = 0

for i in range(len(lst)):
    if lst[i] > amount:
        amount = lst[i]
        tag = i

tag = str(tag)
if len(tag) < 3:
    tag = "0" + tag
print(tag, amount)
