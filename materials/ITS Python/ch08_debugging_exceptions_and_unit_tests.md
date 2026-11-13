# 第 8 章：除錯、例外處理與單元測試

官方第 5 領域有三塊：辨認與修正錯誤、建構 exception handling、使用 `unittest`。只背 `try/except` 會漏掉三分之一以上的概念。

## 1. 三種錯誤

### Syntax error

程式無法被 parser 正確解析。

```python
if score >= 60
    print("pass")
```

少了冒號，通常是 `SyntaxError`。

### Runtime error

語法合法，但執行途中發生 exception。

```python
number = int("hello")  # ValueError
print(10 / 0)          # ZeroDivisionError
```

### Logic error

程式能跑完但答案錯，通常不會自動報錯。

```python
# 想算平均，卻少除一個元素
average = sum(scores) / (len(scores) - 1)
```

Logic error 最難抓，因為電腦很配合地把錯誤想法執行完了。

## 2. 讀 traceback

由 traceback 最底部先看 exception type 與 message，再往上找自己程式中的最後一個 frame。箭頭指的是「偵測到問題的位置」，不一定是根本原因。

常見例外：

| 例外 | 常見原因 |
|---|---|
| `NameError` | 名稱尚未定義或拼錯 |
| `TypeError` | 型別不支援該操作／參數型別錯 |
| `ValueError` | 型別可接受，但值的格式或範圍不合法 |
| `IndexError` | sequence 索引超界 |
| `KeyError` | dict key 不存在 |
| `FileNotFoundError` | 讀取的路徑不存在 |
| `ZeroDivisionError` | 除數為 0 |

## 3. `try` / `except`

```python
try:
    age = int(input("Age: "))
except ValueError:
    print("Age must be an integer")
```

只包住預期可能失敗的最小區域。整支程式外包一個大 `try`，會讓錯誤來源變模糊。

```python
try:
    value = int(text)
except (TypeError, ValueError) as error:
    print(f"Invalid value: {error}")
```

避免裸的 `except:` 或隨手 `except Exception:` 後什麼都不做；那會把真正的 bug 埋掉。

## 4. `else` 與 `finally`

```python
try:
    number = int(text)
except ValueError:
    print("invalid")
else:
    print(number * 2)  # try 沒有例外時執行
finally:
    print("finished") # 不論有無例外都執行
```

精確流程：

- `except`：發生匹配例外時。
- `else`：`try` 正常完成時。
- `finally`：最後一定嘗試執行，常用於 cleanup。

檔案關閉通常用 `with` 比 `finally: file.close()` 更直接。

## 5. `raise`

```python
def set_percentage(value):
    if not 0 <= value <= 100:
        raise ValueError("percentage must be between 0 and 100")
    return value
```

`raise` 主動表示函式契約被破壞，不是「程式壞掉才不得已出現」。在 `except` 中單獨寫 `raise` 可重新拋出目前例外。

## 6. 除錯方法

1. 先建立可穩定重現的最小輸入。
2. 讀 exception type、message 與行號。
3. 對照預期值與實際值，追蹤資料型別。
4. 縮小範圍，不要同時改五件事。
5. 修正後增加 test，避免同一 bug 復活。

`print()` 可以暫時觀察，但 debugger、assertion 與 unit test 更適合可重複驗證。

## 7. `unittest` 基本結構

```python
import unittest


def clamp(value, low, high):
    return max(low, min(value, high))


class TestClamp(unittest.TestCase):
    def test_value_inside_range(self):
        self.assertEqual(clamp(5, 0, 10), 5)

    def test_value_above_range(self):
        self.assertEqual(clamp(99, 0, 10), 10)


if __name__ == "__main__":
    unittest.main()
```

Test class 繼承 `unittest.TestCase`；test method 名稱以 `test` 開頭。

## 8. 官方點名的 assert methods

```python
self.assertIsInstance(value, int)
self.assertEqual(actual, expected)
self.assertTrue(condition)
self.assertIs(result, None)
self.assertIn("python", topics)
```

- `assertEqual(a, b)`：值相等。
- `assertIs(a, b)`：同一物件，常見於 `None`。
- `assertTrue(x)`：truthy。
- `assertIn(member, container)`：成員存在。
- `assertIsInstance(obj, cls)`：型別／子型別符合。

雖未列於官方五個名稱，實務上也應認得：

```python
with self.assertRaises(ValueError):
    set_percentage(101)
```

## 9. `setUp()` 與測試獨立性

```python
class TestScores(unittest.TestCase):
    def setUp(self):
        self.scores = [70, 80, 90]

    def test_total(self):
        self.assertEqual(sum(self.scores), 240)
```

每個 test 都應能獨立執行；不要讓一個 test 依賴另一個 test 先修改狀態。

## 10. 本章考點檢核與練習

- 能分類 syntax、runtime、logic error。
- 能從 traceback 找到 exception type 與問題 frame。
- 能精確說出 `try/except/else/finally` 的執行條件。
- 能使用 `raise` 表達不合法狀態。
- 能寫 `unittest.TestCase`，並使用官方點名的五個 assert methods。

練習：為第 7 章的 `read_scores()` 寫測試，涵蓋正常資料、不存在檔案、格式錯誤三種情況。不要只測 happy path；只測晴天的雨傘，可信度大概跟裝飾品差不多。

## 11. 來源

- [Python 官方教學：Errors and Exceptions](https://docs.python.org/3/tutorial/errors.html)
- [Python 官方文件：unittest](https://docs.python.org/3/library/unittest.html)

