n, m, r, k, t = map(int, input().split())
talent = list(map(int, input().split()))
room = [x // r + 1 for x in range(m * r)]

got_talent = [0] * (n + 1)
got_room = [0] * (m + 1)


def dfs(got_talent, got_room, index, selected, talent, room, k, found):
    if len(selected) == k:
        found += 1
        if found == t:
            print(*selected)
        return found

    if m * r - index < k - len(selected):
        return found

    skill = talent[index]
    classroom = room[index]

    if not got_talent[skill] and got_room[classroom] < 2:
        got_talent[skill] = 1
        got_room[classroom] += 1
        selected.append(index + 1)

        found = dfs(got_talent, got_room, index + 1, selected, talent, room, k, found)

        got_talent[skill] = 0
        got_room[classroom] -= 1
        selected.pop()

        if found == t:
            return found

    return dfs(got_talent, got_room, index + 1, selected, talent, room, k, found)


dfs(got_talent, got_room, 0, [], talent, room, k, 0)