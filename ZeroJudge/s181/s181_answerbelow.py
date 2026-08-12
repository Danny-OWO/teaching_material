from sys import stdin

# n種專長項目
# m個班級
# 每班r個人
# 出去比賽，一隊要有k人
# t:求所有組合按照升序的第t項目

n,m,r,k,t = map(int, input().split())
p = input()

student_specialities =  list(map(int, p.split()))
student_num = list(map(str,range(1,m*r+1)))
student_class = []
for i in range(1,m+1):
    student_class += ([i] * r)

# 紀錄dfs訪問狀態
class_student_count = [0] * m     # 每個班級有派出多少人了
speciality_is_used = [False] * n    # 該專長是否有被使用過

combination = [""] * k  # 紀錄當前訪問狀態
ans_count = 0

# 找到題目瞬間用來退出循環
class FoundAns(Exception):
        pass

def dfs(layer:int, start:int):
    global ans_count
    if layer == k:
        ans_count += 1
        if ans_count == t:
            raise FoundAns()
        return
    for i in range(start, m*r):
        if ans_count == t:
            return
        _spe_index = int(student_specialities[i]) - 1
        _class_index = student_class[i] - 1
        if (not speciality_is_used[_spe_index]) and (class_student_count[_class_index] < 2):
            combination[layer] = i + 1

            class_student_count[_class_index] += 1
            speciality_is_used[_spe_index] = True
            dfs(layer+1, i+1) # 訪問下一層
            speciality_is_used[_spe_index] = False
            class_student_count[_class_index] -= 1

        else:
            continue

try:
    dfs(0, 0)
except FoundAns:
    print(*combination, sep=" ",end="")