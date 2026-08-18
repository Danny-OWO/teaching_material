n = int(input())
def check():
    word = input()
    stack = []
    ans = 0
    for i in word:
        if i == '(':
            stack.append('(')
        elif i == ')':
            if stack:
                stack.pop()
                ans += 1
            else:
                print(0)
                return
                
    if stack:
        print(0)
    else:
        print(ans)
    return

for j in range(n):
    check()