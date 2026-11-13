# 第 6 章：Console I/O、格式化與命令列參數

官方把 I/O 拆成 console 與 file 兩部分。本章處理使用者輸入、螢幕輸出、`str.format()`、f-string 與 command-line arguments。

## 1. `input()` 永遠先回傳字串

```python
age_text = input("Age: ")
age = int(age_text)
```

```python
# 錯誤：若輸入 2 與 3，結果是 "23"
a = input()
b = input()
print(a + b)
```

需要數值運算就明確轉型，也要思考不合法輸入造成的 `ValueError`。

## 2. 一行多個輸入

```python
x_text, y_text = input().split()
x = int(x_text)
y = int(y_text)

# 常見簡寫
x, y = map(int, input().split())
```

左側名稱數量與 split 後項目數量不同時，unpacking 會發生 `ValueError`。

## 3. `print()` 的 `sep` 與 `end`

```python
print("ITS", "Python", sep="-")  # ITS-Python\n
print("loading", end="...")
print("done")                      # loading...done\n
```

`print()` 預設用一個空白分隔多個物件，最後加換行。`sep` 與 `end` 都是 keyword arguments。

## 4. f-string

```python
name = "Ada"
score = 92.567
print(f"{name}: {score:.2f}")       # Ada: 92.57
print(f"{score:8.2f}")             # 欄寬 8，小數 2 位
print(f"{0.875:.1%}")               # 87.5%
```

常用格式：

| 規格 | 用途 | 範例 |
|---|---|---|
| `.2f` | 固定小數 2 位 | `3.14` |
| `8.2f` | 欄寬 8、小數 2 位 | 靠右對齊 |
| `<10` | 靠左，寬 10 | 文字表格 |
| `>10` | 靠右，寬 10 | 文字表格 |
| `^10` | 置中，寬 10 | 標題 |
| `,` | 千分位 | `1,000,000` |
| `.1%` | 百分比 | `87.5%` |

## 5. `str.format()`

官方仍明確列入，不可只學 f-string。

```python
template = "{} scored {:.1f}"
print(template.format("Lin", 88.25))

print("{name}: {score:.2f}".format(name="Lin", score=88.25))
print("{1} before {0}".format("second", "first"))
```

Placeholder 的數量、索引或名稱錯誤可能造成 `IndexError` 或 `KeyError`。

## 6. Escape sequences

```python
print("first\nsecond")
print("name\tscore")
print("She said \"Hi\"")
print("C:\\Users\\Student")
```

Raw string 可減少反斜線跳脫：

```python
path = r"C:\Users\Student"
```

## 7. `sys.argv`

若執行：

```text
python report.py scores.txt 60
```

則：

```python
import sys

print(sys.argv[0])  # report.py
print(sys.argv[1])  # scores.txt
print(sys.argv[2])  # "60"，仍是字串
```

`sys.argv` 是 command-line argument list，索引 0 通常是 script 名稱。存取不存在的索引會發生 `IndexError`。

```python
import sys

if len(sys.argv) != 3:
    print("Usage: python report.py FILE PASS_SCORE")
    raise SystemExit(2)

filename = sys.argv[1]
pass_score = int(sys.argv[2])
```

## 8. Standard streams

```python
import sys

sys.stdout.write("normal output\n")
sys.stderr.write("error message\n")
line = sys.stdin.readline()
```

一般 console I/O 使用 `input()` 與 `print()`；`sys.stdin`、`sys.stdout`、`sys.stderr` 則提供對應的標準 stream。

## 9. 本章考點檢核與練習

- 記得 `input()` 與 `sys.argv` 的元素是字串。
- 能追蹤 `print(..., sep=..., end=...)` 的精確輸出。
- 能使用 f-string 與 `str.format()` 控制小數位、寬度、對齊與百分比。
- 知道 `sys.argv[0]` 的角色並先檢查長度。

練習：寫 `invoice.py PRICE QUANTITY`，由命令列讀入單價與數量，輸出含千分位、兩位小數的總價；參數數量錯誤時輸出 usage。

## 10. 來源

- [Python 官方教學：Input and Output](https://docs.python.org/3/tutorial/inputoutput.html)
- [Python 官方文件：sys.argv](https://docs.python.org/3/library/sys.html#sys.argv)

