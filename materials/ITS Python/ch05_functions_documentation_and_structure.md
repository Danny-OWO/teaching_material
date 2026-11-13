# 第 5 章：函式、Documentation 與程式結構

本章整理縮排、空白、註解、docstring、`help()`、`pydoc`、函式簽名、預設值與回傳值。

## 1. 定義與呼叫函式

```python
def area(width, height):
    return width * height

result = area(3, 4)
```

- `def` 建立函式。
- `width`、`height` 是 parameters。
- `3`、`4` 是 arguments。
- `return` 結束函式並把值交回呼叫端。

若沒有執行到 `return value`，函式回傳 `None`。

```python
def show(message):
    print(message)

value = show("hello")  # 印 hello，value 是 None
```

## 2. Positional 與 keyword arguments

```python
def power(base, exponent):
    return base ** exponent

power(2, 3)
power(base=2, exponent=3)
power(2, exponent=3)
```

一般 positional argument 必須放在 keyword argument 前面。

## 3. Default values

```python
def greet(name, prefix="Hello"):
    return f"{prefix}, {name}!"

greet("Ada")
greet("Ada", "Welcome")
```

有預設值的 parameter 通常要放在沒有預設值者後面。

### Mutable default trap

```python
# 危險：同一個 list 會跨呼叫重用
def add_item(item, bucket=[]):
    bucket.append(item)
    return bucket

# 正確慣用法
def add_item_safely(item, bucket=None):
    if bucket is None:
        bucket = []
    bucket.append(item)
    return bucket
```

## 4. Scope

```python
rate = 1.05  # global

def calculate(price):
    fee = 10  # local
    return price * rate + fee
```

函式內指定的名稱預設是 local。同名的 global 與 local 變數屬於不同 scope。

## 5. Call signature 與 `pass`

`calculate(price, tax=0.05)` 的 signature 包含函式名稱、parameter 順序與預設值。

```python
def not_implemented_yet(value):
    pass
```

`pass` 讓函式語法成立，但呼叫結果仍是 `None`。

## 6. Indentation 與 whitespace

Python 用縮排定義 block；同一 block 的縮排必須一致。一般慣例是每層 4 個空白。

```python
def absolute(value):
    if value < 0:
        return -value
    return value
```

錯誤縮排可能造成 `IndentationError`，也可能改變程式邏輯。

## 7. Comment、docstring 與 `help()`

```python
def celsius_to_fahrenheit(celsius):
    """Convert a Celsius temperature to Fahrenheit."""
    return celsius * 9 / 5 + 32  # conversion formula
```

| 項目 | 位置與用途 |
|---|---|
| Comment | 以 `#` 開始，用來解釋實作原因或限制 |
| Module docstring | module 第一個字串 literal，說明整個檔案 |
| Function docstring | function body 第一個字串 literal，說明參數、行為與回傳 |
| Class docstring | class body 第一個字串 literal，說明類別用途 |
| `obj.__doc__` | 取得物件的 docstring |
| `help(obj)` | 顯示由 signature 與 docstring 組成的文件 |

```python
print(celsius_to_fahrenheit.__doc__)
help(celsius_to_fahrenheit)
```

## 8. `pydoc`

`pydoc` 可從 module 結構、名稱、signature 與 docstring 產生文件。

```text
python -m pydoc my_module
python -m pydoc -w my_module
python -m pydoc -b
```

| 指令 | 功用 |
|---|---|
| `python -m pydoc my_module` | 在 terminal 顯示 module 文件 |
| `python -m pydoc -w my_module` | 產生 HTML 文件 |
| `python -m pydoc -b` | 啟動本機文件瀏覽器 |

## 9. 結構化小程式

```python
def parse_score(text):
    """Convert score text to an integer."""
    return int(text)


def is_passing(score, threshold=60):
    """Return whether score reaches the passing threshold."""
    return score >= threshold


def main():
    score = parse_score(input("Score: "))
    print("Pass" if is_passing(score) else "Fail")


if __name__ == "__main__":
    main()
```

`__name__` guard 的規則見第 9 章。函式可將輸入、處理與輸出分開。

## 10. 本章考點檢核與練習

- 能區分 parameter、argument 與 return value。
- 能依 positional、keyword、default argument 判斷呼叫是否合法。
- 知道無 `return` 的函式回傳 `None`。
- 能辨認縮排造成的 syntax 或 logic error。
- 能撰寫 docstring 並使用 `pydoc`。

練習：把「讀入三個成績並輸出平均與是否及格」拆成至少三個函式，替每個函式加 docstring，再用 `python -m pydoc` 檢查文件。

## 11. 來源

- [Python 官方教學：Defining Functions](https://docs.python.org/3/tutorial/controlflow.html#defining-functions)
- [Python 官方文件：pydoc](https://docs.python.org/3/library/pydoc.html)
- [PEP 257：Docstring Conventions](https://peps.python.org/pep-0257/)

