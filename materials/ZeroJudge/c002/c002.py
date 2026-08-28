def f91(n):
    if n <= 100:
        return f91(f91(n + 11))
    else:
        return n - 10


n = int(input())

while n != 0:
    print(f"f91({n}) = {f91(n)}")
    n = int(input())