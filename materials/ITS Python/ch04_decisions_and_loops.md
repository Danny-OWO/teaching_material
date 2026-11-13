# 第 4 章：條件判斷與迴圈

官方要求的不只是會寫 `if` 與 `for`，而是能建構與分析 nested、compound control flow。

## 1. `if`、`elif`、`else`

```python
score = 82

if score >= 90:
    grade = "A"
elif score >= 80:
    grade = "B"
else:
    grade = "C"
```

只會執行第一個為真的分支。順序有意義；若先判斷 `score >= 60`，後面的 `>= 90` 永遠到不了。

## 2. Compound 與 nested conditions

```python
if age >= 18 and has_id:
    print("allowed")

if logged_in:
    if is_admin:
        print("admin panel")
```

De Morgan's laws 可用來改寫等價條件：

```python
not (a and b) == ((not a) or (not b))
not (a or b) == ((not a) and (not b))
```

## 3. `range()`

```python
range(5)        # 0, 1, 2, 3, 4
range(2, 6)     # 2, 3, 4, 5
range(10, 2, -2) # 10, 8, 6, 4
```

同切片一樣，終點不包含。step 為 0 會發生 `ValueError`。

## 4. `for` 迴圈

```python
total = 0
for number in [3, 5, 7]:
    total += number
print(total)
```

走訪字串時每次取得一個字元：

```python
for char in "ITS":
    print(char)
```

需要索引與值時可使用 `enumerate()`：

```python
for index, value in enumerate([10, 20], start=1):
    print(index, value)
```

## 5. `while` 迴圈

```python
count = 3
while count > 0:
    print(count)
    count -= 1
```

設計 `while` 時要檢查三件事：初始狀態、繼續條件、每輪是否朝終止前進。少任何一項都容易成為無限迴圈。

## 6. `break`、`continue`、`pass`

```python
for value in range(10):
    if value == 7:
        break       # 結束整個迴圈
    if value % 2 == 0:
        continue    # 跳過本輪剩餘內容
    print(value)
```

`pass` 什麼都不做，常用於語法上需要 suite、但尚未實作的地方：

```python
def future_feature():
    pass
```

`continue` 跳過本輪；`break` 結束迴圈；`pass` 不執行任何動作。

## 7. 巢狀迴圈

```python
for row in range(2):
    for column in range(3):
        print(row, column)
```

內層總共執行 `2 * 3 = 6` 次。內層的 `break` 只離開內層，不會自動離開外層。

## 8. Loop `else`

迴圈也可以搭配 `else`：

```python
target = 7
for value in [2, 4, 6]:
    if value == target:
        print("found")
        break
else:
    print("not found")
```

`else` 在迴圈正常結束、沒有被 `break` 中止時執行。它不是「if 的 else」。

## 9. Trace table

面對輸出預測題，畫表通常比在腦中硬轉可靠：

```python
result = 0
for i in range(1, 5):
    if i % 2 == 0:
        result += i
    else:
        result -= 1
```

| `i` | 條件 | `result` |
|---:|---|---:|
| 1 | false | -1 |
| 2 | true | 1 |
| 3 | false | 0 |
| 4 | true | 4 |

## 10. 本章考點檢核與練習

- 能追蹤 nested / compound conditional。
- 能由 `range(start, stop, step)` 列出實際值。
- 能分辨 `break`、`continue`、`pass`。
- 能找到 off-by-one 與無限迴圈。
- 能計算巢狀迴圈的執行次數。

練習：寫一個程式從 1 到 100 找出第一個同時可被 7 整除且大於 50 的數；再修改成找不到時印出訊息，分別使用 flag 與 loop `else` 實作。

## 11. 來源

- [Python 官方教學：More Control Flow Tools](https://docs.python.org/3/tutorial/controlflow.html)

