# 第 1 章：ITS Python 考綱地圖與 Python 基礎

本教材以 **Certiport IT Specialist: Python（ITS-303）2025 官方考綱**為準。官方考綱的 6 個領域在此編排為 9 章。

考試內容包含閱讀、撰寫、除錯及維護 Python 3 程式。官方建議具備至少 **150 小時**的課程或實作經驗。

## 1. 九章與官方考綱的對照

| 本教材 | 主題 | 對應官方 objective |
|---|---|---|
| 1 | 考綱、型別、變數、轉型 | 1.1、1.2 |
| 2 | 運算子、字串、索引與切片 | 1.2、1.3、1.4 |
| 3 | list 與資料結構 | 1.2 |
| 4 | 判斷與迴圈 | 2.1、2.2 |
| 5 | 函式、文件與程式結構 | 4.1、4.2 |
| 6 | Console I/O、格式化與命令列 | 3.2、6.1 |
| 7 | File I/O 與檔案系統 | 3.1、6.1 |
| 8 | 除錯、例外與單元測試 | 5.1、5.2、5.3 |
| 9 | 模組與標準函式庫 | 6.1、6.2 |

## 2. 四個官方點名的基本型別

```python
name = "Ada"       # str
attempts = 3        # int
score = 92.5        # float
passed = True       # bool
```

使用 `type()` 可以取得值的型別：

```python
print(type(name))      # <class 'str'>
print(type(attempts))  # <class 'int'>
```

Python 是動態型別語言：變數名稱本身沒有永遠固定的型別，它在當下參考某個物件。

```python
x = 10
x = "ten"  # 合法，但若濫用會讓程式難追蹤
```

## 3. Literal 與指定

```python
count = 42
temperature = -3.5
message = 'hello'
is_ready = False
nothing = None
```

`=` 是 assignment，不是數學上的相等。右邊先計算，再把結果指定給左邊名稱。

```python
x = 5
x = x + 1  # 右側舊的 x 先算出 6，再重新指定
```

變數名稱區分大小寫，`score` 與 `Score` 是不同名稱。名稱不能以數字開頭，也不能使用 `if`、`for`、`class` 等關鍵字。

## 4. 型別轉換

```python
age_text = "18"
age = int(age_text)       # 18
price = float("49.5")     # 49.5
label = str(2026)         # "2026"
flag = bool(1)            # True
```

轉型必須符合目標型別的格式：

```python
int(3.9)      # 3，朝 0 截斷，不是四捨五入
int("3.9")    # ValueError，字串不是合法整數格式
float("3.9")  # 3.9
```

常見 falsy 值包括 `False`、`None`、數值 `0`，以及空字串或空容器；其他值通常為 truthy。

```python
bool(0)       # False
bool("")      # False
bool([])      # False
bool("False") # True：它是非空字串
```

## 5. 可變與不可變

- `int`、`float`、`bool`、`str`、`tuple` 是 immutable。
- `list`、`dict`、`set` 是 mutable。

```python
text = "cat"
# text[0] = "C"  # TypeError：str 不可原地修改
text = "C" + text[1:]

numbers = [1, 2, 3]
numbers[0] = 99  # list 可以修改
```

這個差異會影響函式傳參、`is`、複製與 list 操作。

## 6. 必須能手算的片段

```python
x = "12"
y = 3
print(x * y)
```

答案是 `121212`，因為字串乘整數代表重複，不是數值乘法。

```python
value = 0
print(bool(value), str(value), float(value))
```

輸出為 `False 0 0.0`。

## 7. 本章考點檢核

- 能由 expression 判斷結果是 `str`、`int`、`float` 或 `bool`。
- 能判斷合法與不合法的型別轉換。
- 理解 `input()` 的結果永遠先是字串。
- 能區分 mutable 與 immutable，而不是把「變數可重新指定」誤認成「物件可修改」。
- 不把 `=` 與 `==` 混在一起。

## 8. 練習

1. 不執行程式，寫出 `type(5 / 2)`、`type(5 // 2)`、`type("5" * 2)`。
2. 解釋為何 `bool("0")` 是 `True`。
3. 寫一段程式讀入半徑，轉成 `float` 後計算圓面積。
4. 找出 `int(input()) + 1` 可能發生的 runtime error，並舉出一個輸入。

## 9. 來源

- [Certiport ITS Python 2025 Exam Objectives](https://certiport.ccilearning.com/wp-content/uploads/2025/06/ITS-OD-303-Python-0225.pdf)
- [Python 官方教學：An Informal Introduction to Python](https://docs.python.org/3/tutorial/introduction.html)

