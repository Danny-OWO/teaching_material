# 第 9 章：Modules、Tools 與標準函式庫

官方第 6 領域不是泛泛地說「會 import 就好」，而是明列 `io`、`os`、`os.path`、`sys`、`math`、`datetime`、`random` 與一串指定成員。本章就是那張不可含糊的清單。

## 1. Import forms

```python
import math
print(math.sqrt(25))

from math import sqrt, pi
print(sqrt(25), pi)

import datetime as dt
print(dt.datetime.now())
```

- `import math` 保留 module namespace，來源最清楚。
- `from math import sqrt` 把名稱直接放進目前 namespace。
- `as` 建立 alias。
- 避免 `from module import *`，因為名稱來源不明且可能衝突。

## 2. 自訂 module 與 `__name__`

一個 `.py` 檔就是 module。假設 `converter.py`：

```python
def c_to_f(value):
    return value * 9 / 5 + 32


if __name__ == "__main__":
    print(c_to_f(0))
```

另一檔案：

```python
import converter

print(converter.c_to_f(100))
```

直接執行 `converter.py` 時，`__name__ == "__main__"`；被 import 時則通常是 module 名稱，所以 guard 內的示範或 CLI 程式不會意外執行。

## 3. `math` 官方指定清單

```python
import math

math.fabs(-3.5)      # 3.5，float
math.ceil(3.2)       # 4
math.floor(3.8)      # 3
math.trunc(-3.8)     # -3，朝 0 截斷
math.fmod(-7, 3)     # -1.0，符號規則與 % 不同
math.frexp(8.0)      # (0.5, 4)，x = m * 2**e
math.nan             # NaN
math.isnan(math.nan) # True；不要用 == 判斷 NaN
math.sqrt(9)         # 3.0
math.isqrt(10)       # 3，非負整數平方根向下取整
math.pow(2, 3)       # 8.0
math.pi              # 圓周率常數
```

尖銳但重要的差異：

- `math.pow()` 會轉為 float；內建 `pow()` / `**` 可保留整數。
- `math.trunc(-3.8) == -3`，`math.floor(-3.8) == -4`。
- `math.nan == math.nan` 是 `False`，要用 `math.isnan()`。

## 4. `datetime` 官方指定清單

```python
from datetime import datetime

now = datetime.now()
text = now.strftime("%Y-%m-%d %H:%M")
day = now.weekday()
```

- `datetime.now()`：目前本地日期時間。
- `strftime(format)`：將 datetime 格式化為字串。
- `weekday()`：Monday 是 `0`，Sunday 是 `6`。

常見 format codes：`%Y` 四位年、`%m` 月、`%d` 日、`%H` 24 小時、`%M` 分、`%S` 秒。

## 5. `random` 官方指定清單

```python
import random

random.randrange(1, 10, 2)  # 1, 3, 5, 7, 9 之一；stop 不含
random.randint(1, 6)        # 1 到 6，兩端都含
random.random()             # 0.0 <= x < 1.0

items = [1, 2, 3, 4]
random.shuffle(items)       # 原地修改，回傳 None
random.choice(items)        # 隨機一項
random.sample(items, 2)     # 不重複抽 2 項，回傳新 list
```

`choice()` 抽一項；`sample()` 抽多項且不重複；`shuffle()` 直接改原 list。這三個的回傳與副作用非常愛考。

## 6. `os` 與 `os.path`

```python
import os

current = os.getcwd()
names = os.listdir(current)
path = os.path.join(current, "data.txt")
exists = os.path.exists(path)
is_file = os.path.isfile(path)
```

刪除檔案使用 `os.remove(path)`。檔案的 open/read/write 與存在檢查已在第 7 章完整處理。

## 7. `sys`

```python
import sys

arguments = sys.argv
python_version = sys.version
module_paths = sys.path
sys.exit(1)
```

- `sys.argv`：CLI arguments。
- `sys.path`：import 搜尋路徑 list。
- `sys.exit()`：以 `SystemExit` 結束程式；0 通常代表成功，非 0 代表錯誤。

## 8. `io`

```python
import io

text_stream = io.StringIO("first\nsecond\n")
print(text_stream.readline())

byte_stream = io.BytesIO(b"ABC")
print(byte_stream.read())
```

- `StringIO` 處理 `str`。
- `BytesIO` 處理 `bytes`。
- 它們提供 file-like API，可用來測試不想碰實體檔案的程式。

## 9. 綜合範例

```python
import math
import random
from datetime import datetime


def build_report(values):
    """Return a timestamped report for numeric values."""
    chosen = random.choice(values)
    return {
        "created": datetime.now().strftime("%Y-%m-%d %H:%M"),
        "chosen": chosen,
        "root": math.sqrt(chosen),
        "weekday": datetime.now().weekday(),
    }
```

考題可能同時測 module member、回傳型別與副作用。逐行標出每個呼叫的輸入、輸出型別、是否修改原物件，會比死背函式名有效。

## 10. 九章總複習策略

1. 先用官方 objective 當 checklist，不要只照課本目錄讀。
2. 每個語法都練「預測輸出、找錯、補程式、從零寫」四種題型。
3. 對 list、file、exception、module functions 建立「參數／回傳／副作用／可能例外」四欄表。
4. 至少完成一次限時實作。Next Generation 版本可能包含在 VS Code 中完成的 lab tasks。
5. 錯題要記錄錯誤模型，例如「把 `sort()` 當成有回傳 list」，不要只抄正確答案。

## 11. 最終考點檢核

- 能選擇正確 import form 並追蹤 namespace。
- 能說明 `__name__ == "__main__"`。
- 熟悉官方列出的每一個 `math`、`datetime`、`random` 成員。
- 能區分 `randrange` 與 `randint`、`choice` 與 `sample`、`shuffle` 的副作用。
- 能以 `io`、`os`、`os.path`、`sys` 完成檔案與命令列工作。

## 12. 來源

- [Certiport ITS Python 2025 Exam Objectives](https://certiport.ccilearning.com/wp-content/uploads/2025/06/ITS-OD-303-Python-0225.pdf)
- [Python 官方教學：Modules](https://docs.python.org/3/tutorial/modules.html)
- [Python 官方文件：math](https://docs.python.org/3/library/math.html)
- [Python 官方文件：datetime](https://docs.python.org/3/library/datetime.html)
- [Python 官方文件：random](https://docs.python.org/3/library/random.html)
- [Python 官方文件：os](https://docs.python.org/3/library/os.html)
- [Python 官方文件：sys](https://docs.python.org/3/library/sys.html)
- [Python 官方文件：io](https://docs.python.org/3/library/io.html)

