# 第 2 章：運算子、字串、索引與切片

本章整理運算子的執行順序，以及字串的索引與切片。

## 1. 算術運算子

| 運算子 | 意義 | 範例 | 結果 |
|---|---|---|---|
| `+` | 加法／串接 | `7 + 2` | `9` |
| `-` | 減法 | `7 - 2` | `5` |
| `*` | 乘法／重複 | `"a" * 3` | `"aaa"` |
| `/` | 真除法 | `7 / 2` | `3.5` |
| `//` | floor division | `7 // 2` | `3` |
| `%` | 餘數 | `7 % 2` | `1` |
| `**` | 次方 | `2 ** 3` | `8` |

`//` 是向負無限大取整，不是單純砍掉小數：

```python
7 // 2    # 3
-7 // 2   # -4
```

## 2. 優先順序與結合方向

常用的簡化順序：

1. `()`
2. `**`（由右向左）
3. unary `+x`、`-x`
4. `*`、`/`、`//`、`%`
5. `+`、`-`
6. comparison、`is`、`in`
7. `not`
8. `and`
9. `or`

```python
2 + 3 * 4       # 14
(2 + 3) * 4     # 20
2 ** 3 ** 2     # 2 ** (3 ** 2) = 512
```

括號可以明確指定計算順序。

## 3. 指定運算子

```python
x = 10
x += 3   # 13
x -= 2   # 11
x /= 2   # 5.5，/ 的結果通常是 float
x //= 2  # 2.0，左值原本是 float
x **= 3  # 8.0
x %= 3   # 2.0
```

官方列出的指定運算子包括 `=`、`+=`、`-=`、`/=`、`%=`、`//=`、`**=`。

## 4. 比較、邏輯、身分與成員

```python
age >= 18
score != 0
10 <= x < 20       # chained comparison
is_admin and active
not finished
"py" in "python"   # True
3 not in [1, 2]    # True
```

`and` 與 `or` 會 short-circuit，而且回傳的不一定是 `bool`：

```python
"" or "fallback"  # "fallback"
"ok" and 42       # 42
```

### `==` 與 `is` 不是同義詞

- `==` 比較值是否相等。
- `is` 比較是否為同一個物件。

```python
a = [1, 2]
b = [1, 2]
a == b  # True
a is b  # False

value is None  # 檢查 None 的慣用寫法
```

數字或字串的內容使用 `==` 比較；`is` 用於物件身分，例如 `value is None`。

## 5. 字串索引

```python
word = "Python"
word[0]   # "P"
word[5]   # "n"
word[-1]  # "n"
word[-2]  # "o"
```

索引超出範圍會發生 `IndexError`。長度為 `n` 的字串，合法正索引為 `0` 到 `n - 1`。

## 6. 切片

格式是 `sequence[start:stop:step]`，`stop` 不包含在結果內。

```python
word = "Python"
word[1:4]   # "yth"
word[:3]    # "Pyt"
word[3:]    # "hon"
word[::2]   # "Pto"
word[::-1]  # "nohtyP"
```

切片超出範圍通常不會報錯，而是安全地截到邊界；單一索引則會報錯。

## 7. 常用字串操作

```python
text = "  Python Exam  "
text.strip()                 # "Python Exam"
text.lower()                 # "  python exam  "
text.upper()
text.replace("Exam", "Lab")
text.split()                 # ["Python", "Exam"]
"-".join(["ITS", "303"])  # "ITS-303"
text.find("Python")          # 2；找不到回傳 -1
len(text)
```

字串方法通常回傳新字串，不會修改原字串。

## 8. 型別不同時的運算結果

```python
"10" + "5"  # "105"
10 + 5        # 15
# "10" + 5   # TypeError
```

```python
False == 0    # True
False is 0    # False，而且這樣比較本來就不該寫
```

## 9. 本章考點檢核與練習

- 能手算混合 `**`、`//`、`%`、比較與邏輯運算的 expression。
- 能說明 negative floor division。
- 能區分 `==`、`is`、`in`。
- 能正確追蹤負索引與 `[start:stop:step]`。
- 知道字串是 immutable。

練習：不執行程式，求出 `3 + 8 // 3 ** 2`、`"abcdef"[-4:-1]`、`0 or 5 and 2` 的結果，並寫出推理順序。

## 10. 來源

- [Python Language Reference：Expressions](https://docs.python.org/3/reference/expressions.html)
- [Python 官方教學：Strings](https://docs.python.org/3/tutorial/introduction.html#text)

