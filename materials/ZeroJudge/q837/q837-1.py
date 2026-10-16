m, n, k = map(int, input().split())
words = [input() for _ in range(m)]
positions = [0] * m

answer = 0

for _ in range(k):
    shifts = list(map(int, input().split()))

    for row in range(m):
        positions[row] = (positions[row] - shifts[row]) % n

    for col in range(n):
        counts = {}
        best = 0

        for row in range(m):
            char = words[row][(positions[row] + col) % n]
            counts[char] = counts.get(char, 0) + 1
            best = max(best, counts[char])

        answer += best

print(answer)