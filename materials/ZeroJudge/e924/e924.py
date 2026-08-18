n = int(input())

def check():
    word = input()
    stack = []

    for cur in word:
        tag = 0

        if cur == '(':
            tag = 1
        elif cur == '[':
            tag = 2
        elif cur == '{':
            tag = 3
        elif cur == '<':
            tag = 4
        elif cur == ')':
            tag = -1
        elif cur == ']':
            tag = -2
        elif cur == '}':
            tag = -3
        elif cur == '>':
            tag = -4

        if tag > 0:
            stack.append(tag)
        else:
            if not stack:
                print('N')
                return

            if stack[-1] + tag == 0:
                stack.pop()
            else:
                print('N')
                return

    if not stack:
        print('Y')
    else:
        print('N')


for _ in range(n):
    check()