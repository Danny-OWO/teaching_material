s1 = []
s2 = []

while True:
    try:
        command = input().split()
    except EOFError:
        break

    if command[0] == "push":
        s1.append(int(command[1]))
        print(1, end="")

    elif command[0] == "pop":
        if not s2:
            while s1:
                s2.append(s1.pop())
                print(5, end="")

        s2.pop()
        print(4, end="")