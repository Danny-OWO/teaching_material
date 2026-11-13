# 第 3 章：List 與資料結構操作

2025 考綱特別把 list 操作寫得比舊版更明確：排序、合併、附加、插入、移除、最大最小與反轉都在範圍內。

## 1. 建立資料結構

```python
numbers = [3, 1, 4]                  # list：有序、可變
point = (10, 20)                     # tuple：有序、不可變
profile = {"name": "Lin", "age": 18}  # dict：key 對應 value
tags = {"python", "exam"}          # set：不重複、無索引
```

官方主要點名 list；「construct data structures」亦涵蓋常見資料結構的建立與讀取。

## 2. List 索引與切片

```python
values = [10, 20, 30, 40]
values[0]       # 10
values[-1]      # 40
values[1:3]     # [20, 30]
values[::-1]    # [40, 30, 20, 10]
```

切片會建立新 list；指定單一索引則修改原 list。

```python
copy_part = values[:]
values[1] = 99
```

## 3. 新增與合併

```python
items = [1, 2]
items.append(3)         # [1, 2, 3]：加入一個元素
items.insert(1, 99)     # [1, 99, 2, 3]
items.extend([4, 5])    # 把多個元素接到原 list
merged = items + [6, 7] # 建立新 list
```

`append()` 與 `extend()` 的差異：

```python
items.append([4, 5])  # 加入一個巢狀 list
items.extend([4, 5])  # 加入兩個元素
```

`append()`、`insert()`、`extend()` 會原地修改並回傳 `None`。

```python
numbers = [3, 1, 2]
result = numbers.sort()
print(result)  # None，不是排序後的 list
```

## 4. 移除元素

```python
items = [10, 20, 20, 30]
items.remove(20)  # 只移除第一個值為 20 的元素
last = items.pop()   # 移除並回傳最後一項
first = items.pop(0) # 移除並回傳索引 0
del items[0]         # 依索引刪除，不回傳值
items.clear()        # 清空
```

- `remove(value)` 找不到值時是 `ValueError`。
- `pop(index)` 索引不存在時是 `IndexError`。
- `del` 是 statement，不是 list method。

## 5. 排序、反轉、最大與最小

```python
scores = [70, 95, 80]
scores.sort()                    # 原地改成 [70, 80, 95]
scores.sort(reverse=True)        # 由大到小
new_scores = sorted(scores)      # 回傳新 list
scores.reverse()                 # 原地反轉目前順序
reversed_copy = scores[::-1]     # 建立反向副本

highest = max(scores)
lowest = min(scores)
total = sum(scores)
count = len(scores)
```

`sort()` 是排序；`reverse()` 只是反轉現有順序。把 `[3, 1, 2]` reverse 會得到 `[2, 1, 3]`，不是降冪排序。

## 6. 搜尋與成員判斷

```python
names = ["Ada", "Lin", "Ada"]
"Lin" in names       # True
names.index("Ada")   # 0，只回傳第一個位置
names.count("Ada")   # 2
```

## 7. Alias 與複製

```python
a = [1, 2]
b = a
b.append(3)
print(a)  # [1, 2, 3]，a 與 b 指向同一個 list

c = a.copy()
c.append(4)
print(a)  # 仍是 [1, 2, 3]
```

`copy()`、`[:]`、`list(a)` 都只做 shallow copy。巢狀物件仍可能共享：

```python
a = [[1], [2]]
b = a.copy()
b[0].append(99)
print(a)  # [[1, 99], [2]]
```

## 8. Tuple、dict 與 set

```python
point = (3, 4)
x, y = point

student = {"name": "Kai", "score": 90}
student["score"] = 95
student.get("rank", "N/A")
for key, value in student.items():
    print(key, value)

seen = {1, 2, 2, 3}  # {1, 2, 3}
seen.add(4)
seen.discard(99)      # 不存在也不報錯
```

空 set 要寫 `set()`；`{}` 是空 dict。

## 9. List comprehension

List comprehension 可用一個 expression 建立 list：

```python
squares = [x * x for x in range(5)]
evens = [x for x in range(10) if x % 2 == 0]
```


## 10. 本章考點檢核與練習

- 分清 `append` 與 `extend`、`remove` 與 `pop`、`sort` 與 `sorted`。
- 知道哪些方法原地修改並回傳 `None`。
- 能判斷 alias 造成的連動修改。
- 能使用 `max`、`min`、`reverse`、`index`、`count`。

練習：建立成績 list，移除最低分、加入補考成績、由高到低排序，再輸出最高分與最低分。刻意同時寫一版使用原地操作、一版保留原 list。

## 11. 來源

- [Python 官方教學：More on Lists](https://docs.python.org/3/tutorial/datastructures.html#more-on-lists)
- [Python 官方教學：Data Structures](https://docs.python.org/3/tutorial/datastructures.html)

