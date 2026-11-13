# 第 9 章：Modules、Documentation 與標準函式庫

本章整理 ITS Python 考綱中的 `io`、`os`、`os.path`、`sys`、`math`、`datetime`、`random`，並補充程式文件工具 `pydoc`。

## 1. 匯入 module

```python
import math
print(math.sqrt(25))

from math import sqrt, pi
print(sqrt(25), pi)

import datetime as dt
print(dt.datetime.now())
```

| 寫法 | 名稱的使用方式 |
|---|---|
| `import math` | `math.sqrt(25)` |
| `import math as m` | `m.sqrt(25)` |
| `from math import sqrt` | `sqrt(25)` |
| `from math import sqrt as root` | `root(25)` |

`from module import *` 可能覆蓋現有名稱，一般不使用。

## 2. 自訂 module 與 `__name__`

每個 `.py` 檔案都可以作為 module。

```python
# converter.py
def c_to_f(value):
    return value * 9 / 5 + 32


if __name__ == "__main__":
    print(c_to_f(0))
```

```python
# app.py
import converter

print(converter.c_to_f(100))
```

| 執行方式 | `converter.py` 中的 `__name__` |
|---|---|
| `python converter.py` | `"__main__"` |
| `import converter` | `"converter"` |

## 3. `math`

```python
import math
```

### 常數與判斷

| 成員 | 功用 | 範例結果 |
|---|---|---|
| `math.pi` | 圓周率 | 約 `3.141592653589793` |
| `math.e` | 自然常數 | 約 `2.718281828459045` |
| `math.nan` | Not a Number | `nan` |
| `math.inf` | 正無限大 | `inf` |
| `math.isnan(x)` | 判斷是否為 NaN | `math.isnan(math.nan)` → `True` |
| `math.isfinite(x)` | 判斷是否為有限數 | `math.isfinite(math.inf)` → `False` |
| `math.isinf(x)` | 判斷是否為無限大 | `math.isinf(math.inf)` → `True` |

NaN 不使用 `==` 判斷：`math.nan == math.nan` 的結果是 `False`。

### 取整與絕對值

| 函式 | 功用 | 範例結果 |
|---|---|---|
| `math.fabs(x)` | 絕對值，回傳 `float` | `math.fabs(-3)` → `3.0` |
| `math.ceil(x)` | 向正無限大取整 | `math.ceil(3.2)` → `4` |
| `math.floor(x)` | 向負無限大取整 | `math.floor(-3.2)` → `-4` |
| `math.trunc(x)` | 朝 0 截斷 | `math.trunc(-3.8)` → `-3` |

### 次方、根號與餘數

| 函式 | 功用 | 範例結果 |
|---|---|---|
| `math.sqrt(x)` | 平方根，回傳 `float` | `math.sqrt(9)` → `3.0` |
| `math.isqrt(n)` | 非負整數平方根向下取整 | `math.isqrt(10)` → `3` |
| `math.pow(x, y)` | 計算 `x` 的 `y` 次方，回傳 `float` | `math.pow(2, 3)` → `8.0` |
| `math.fmod(x, y)` | 浮點餘數，結果符號跟隨 `x` | `math.fmod(-7, 3)` → `-1.0` |
| `math.frexp(x)` | 分解為 `(m, e)`，使 `x == m * 2**e` | `math.frexp(8)` → `(0.5, 4)` |
| `math.gcd(a, b)` | 最大公因數 | `math.gcd(12, 18)` → `6` |
| `math.lcm(a, b)` | 最小公倍數 | `math.lcm(12, 18)` → `36` |

`math.pow()` 回傳 `float`；內建 `pow()` 與 `**` 可保留整數結果。

## 4. `datetime`

```python
from datetime import date, time, datetime, timedelta, timezone
```

### 主要類別

| 類別 | 表示內容 | 建立範例 |
|---|---|---|
| `date` | 年、月、日 | `date(2026, 11, 13)` |
| `time` | 時、分、秒、微秒 | `time(14, 30, 0)` |
| `datetime` | 日期與時間 | `datetime(2026, 11, 13, 14, 30)` |
| `timedelta` | 一段時間差 | `timedelta(days=7, hours=3)` |
| `timezone` | 固定 UTC offset | `timezone.utc` |

### 常用建構與轉換函式

| 函式或方法 | 功用 | 範例 |
|---|---|---|
| `date.today()` | 目前本地日期 | `date.today()` |
| `datetime.now()` | 目前本地日期時間 | `datetime.now()` |
| `datetime.now(timezone.utc)` | 目前 UTC 日期時間 | `datetime.now(timezone.utc)` |
| `datetime.combine(d, t)` | 合併 `date` 與 `time` | `datetime.combine(d, t)` |
| `datetime.strptime(text, format)` | 依格式把字串解析為 `datetime` | `datetime.strptime("2026-11-13", "%Y-%m-%d")` |
| `datetime.fromtimestamp(value)` | Unix timestamp 轉成本地 `datetime` | `datetime.fromtimestamp(0)` |
| `dt.timestamp()` | `datetime` 轉為 Unix timestamp | `dt.timestamp()` |
| `dt.strftime(format)` | 將日期時間格式化為字串 | `dt.strftime("%Y-%m-%d")` |
| `dt.isoformat()` | 轉為 ISO 8601 字串 | `"2026-11-13T14:30:00"` |
| `dt.replace(...)` | 建立替換指定欄位的新物件 | `dt.replace(hour=9)` |

`strptime` 是 string parse time；`strftime` 是 string format time。

### 日期資訊與運算

| 方法或屬性 | 功用 | 結果 |
|---|---|---|
| `dt.year` | 年 | `2026` |
| `dt.month` | 月 | `11` |
| `dt.day` | 日 | `13` |
| `dt.hour` | 小時 | `14` |
| `dt.minute` | 分鐘 | `30` |
| `dt.second` | 秒 | `0` |
| `dt.weekday()` | 星期一為 0，星期日為 6 | `0`～`6` |
| `dt.isoweekday()` | 星期一為 1，星期日為 7 | `1`～`7` |
| `delta.days` | `timedelta` 的天數部分 | `int` |
| `delta.seconds` | 扣除完整天數後的秒數 | `0`～`86399` |
| `delta.total_seconds()` | 完整時間差換算為秒 | `float` |

```python
start = datetime(2026, 11, 13, 9, 0)
end = start + timedelta(days=2, hours=3)
gap = end - start

print(end)
print(gap.total_seconds())
```

### `strftime()` / `strptime()` 格式碼

大小寫不同時代表不同欄位，例如 `%m` 是月份，`%M` 是分鐘。

| 格式碼 | 意義 | 範例 |
|---|---|---|
| `%Y` | 四位數年份 | `2026` |
| `%y` | 兩位數年份 | `26` |
| `%m` | 月份，補零 | `01`～`12` |
| `%B` | 完整月份名稱 | `November` |
| `%b` | 縮寫月份名稱 | `Nov` |
| `%d` | 月中的日期，補零 | `01`～`31` |
| `%A` | 完整星期名稱 | `Friday` |
| `%a` | 縮寫星期名稱 | `Fri` |
| `%w` | 星期日為 0 的星期編號 | `0`～`6` |
| `%j` | 一年中的第幾天，補零 | `001`～`366` |
| `%H` | 24 小時制小時 | `00`～`23` |
| `%I` | 12 小時制小時 | `01`～`12` |
| `%p` | AM／PM | `AM`、`PM` |
| `%M` | 分鐘 | `00`～`59` |
| `%S` | 秒 | `00`～`59` |
| `%f` | 微秒，六位數 | `000000`～`999999` |
| `%z` | UTC offset | `+0800` |
| `%Z` | 時區名稱 | `UTC` |
| `%x` | Locale 日期表示 | 依系統設定 |
| `%X` | Locale 時間表示 | 依系統設定 |
| `%c` | Locale 日期與時間表示 | 依系統設定 |
| `%%` | 百分比符號 | `%` |

```python
dt = datetime(2026, 11, 13, 14, 5, 9)

print(dt.strftime("%Y-%m-%d %H:%M:%S"))
# 2026-11-13 14:05:09

parsed = datetime.strptime("13/11/2026 02:05 PM", "%d/%m/%Y %I:%M %p")
```

## 5. `random`

```python
import random
```

| 函式 | 功用 | 範圍或副作用 |
|---|---|---|
| `random.random()` | 產生浮點亂數 | `0.0 <= x < 1.0` |
| `random.randrange(stop)` | 從 `range(stop)` 選一個整數 | 不包含 `stop` |
| `random.randrange(start, stop, step)` | 從指定 `range` 選一個整數 | 不包含 `stop` |
| `random.randint(a, b)` | 產生整數 | 兩端都包含，等同 `randrange(a, b + 1)` |
| `random.choice(seq)` | 從非空 sequence 選一項 | 回傳一個元素 |
| `random.choices(seq, k=n)` | 可重複抽樣 | 回傳長度 `n` 的 list |
| `random.sample(population, k)` | 不重複抽樣 | 回傳新 list，不修改來源 |
| `random.shuffle(values)` | 打亂 mutable sequence | 原地修改，回傳 `None` |
| `random.uniform(a, b)` | 產生指定範圍浮點數 | 端點是否包含受浮點運算影響 |
| `random.seed(value)` | 設定亂數種子 | 相同種子可重現序列 |

```python
items = [1, 2, 3, 4]
picked = random.choice(items)
two_items = random.sample(items, 2)
random.shuffle(items)
```

`random` 不適合密碼、token 等安全用途；安全亂數使用 `secrets` module。

## 6. `os` 與 `os.path`

```python
import os
import os.path
```

### `os`

| 函式或成員 | 功用 |
|---|---|
| `os.getcwd()` | 取得目前工作目錄 |
| `os.chdir(path)` | 改變目前工作目錄 |
| `os.listdir(path=".")` | 列出目錄中的名稱 |
| `os.mkdir(path)` | 建立一層目錄 |
| `os.makedirs(path, exist_ok=False)` | 建立多層目錄 |
| `os.remove(path)` | 刪除檔案 |
| `os.rename(src, dst)` | 重新命名或移動 |
| `os.rmdir(path)` | 刪除空目錄 |
| `os.environ` | 環境變數 mapping |

### `os.path`

| 函式 | 功用 |
|---|---|
| `os.path.exists(path)` | 路徑是否存在 |
| `os.path.isfile(path)` | 是否為一般檔案 |
| `os.path.isdir(path)` | 是否為目錄 |
| `os.path.join(*parts)` | 依作業系統組合路徑 |
| `os.path.abspath(path)` | 取得正規化絕對路徑 |
| `os.path.basename(path)` | 取得最後一段名稱 |
| `os.path.dirname(path)` | 取得上層路徑 |
| `os.path.split(path)` | 分成 `(dirname, basename)` |
| `os.path.splitext(path)` | 分成 `(root, extension)` |
| `os.path.getsize(path)` | 取得檔案大小，單位為 byte |

```python
path = os.path.join("data", "scores.txt")

if os.path.isfile(path):
    print(os.path.getsize(path))
```

## 7. `sys`

```python
import sys
```

| 成員 | 功用 |
|---|---|
| `sys.argv` | 命令列參數 list；`argv[0]` 通常是 script 名稱 |
| `sys.path` | import 搜尋路徑 list |
| `sys.version` | Python 版本字串 |
| `sys.version_info` | Python 版本資訊 tuple-like object |
| `sys.platform` | 平台識別字串 |
| `sys.stdin` | 標準輸入 stream |
| `sys.stdout` | 標準輸出 stream |
| `sys.stderr` | 標準錯誤 stream |
| `sys.exit(code)` | 引發 `SystemExit` 結束程式 |

```python
import sys

if len(sys.argv) != 2:
    print("Usage: python app.py FILE", file=sys.stderr)
    sys.exit(2)

filename = sys.argv[1]
```

## 8. `io` 與 file-like objects

```python
import io
```

| 類別 | 資料型別 | 功用 |
|---|---|---|
| `io.StringIO` | `str` | 記憶體中的文字 stream |
| `io.BytesIO` | `bytes` | 記憶體中的 binary stream |
| `io.TextIOBase` | `str` | 文字 stream 的基底類別 |
| `io.BufferedIOBase` | `bytes` | buffered binary stream 的基底類別 |

常用 file-like 方法：

| 方法 | 功用 |
|---|---|
| `read(size=-1)` | 讀取內容 |
| `readline()` | 讀取一行 |
| `write(data)` | 寫入資料，回傳寫入數量 |
| `seek(offset, whence=0)` | 移動 cursor |
| `tell()` | 取得 cursor 位置 |
| `getvalue()` | `StringIO`／`BytesIO` 取得全部內容 |
| `close()` | 關閉 stream |

```python
buffer = io.StringIO()
buffer.write("hello")
buffer.write(" world")
print(buffer.getvalue())  # hello world

buffer.seek(0)
print(buffer.read())
buffer.close()
```

## 9. 程式文件：docstring、`help()` 與 `pydoc`

```python
def area(width, height):
    """Return the area of a rectangle."""
    return width * height
```

| 工具 | 功用 | 範例 |
|---|---|---|
| `obj.__doc__` | 取得物件的 docstring | `area.__doc__` |
| `help(obj)` | 在互動環境顯示文件 | `help(area)` |
| `pydoc.render_doc(obj)` | 將文件產生為字串 | `pydoc.render_doc(area)` |
| `python -m pydoc module` | 在 terminal 顯示 module 文件 | `python -m pydoc math` |
| `python -m pydoc -w module` | 產生 HTML 文件 | `python -m pydoc -w converter` |
| `python -m pydoc -b` | 啟動本機文件瀏覽器 | 在 terminal 執行 |

```python
import pydoc

print(area.__doc__)
print(pydoc.render_doc(area))
```

Module、class、function 的 docstring 必須是 body 中的第一個字串 literal。

## 10. 考點檢核

- 能判斷不同 import 寫法建立了哪些名稱。
- 能說明 `__name__ == "__main__"` 的用途。
- 能使用 `math` 的取整、根號、次方、NaN 與常數功能。
- 能建立及運算 `date`、`time`、`datetime`、`timedelta`。
- 能區分 `%m`（月份）與 `%M`（分鐘），並使用 `strptime`、`strftime`。
- 能區分 `randrange`、`randint`、`choice`、`sample`、`shuffle`。
- 能使用 `os`、`os.path`、`sys` 與 `io` 完成檔案和命令列操作。
- 能使用 docstring、`help()` 與 `pydoc` 產生程式文件。

## 11. 來源

- [Certiport ITS Python 2025 Exam Objectives](https://certiport.ccilearning.com/wp-content/uploads/2025/06/ITS-OD-303-Python-0225.pdf)
- [Python 官方教學：Modules](https://docs.python.org/3/tutorial/modules.html)
- [Python 官方文件：math](https://docs.python.org/3/library/math.html)
- [Python 官方文件：datetime](https://docs.python.org/3/library/datetime.html)
- [Python 官方文件：strftime() and strptime() Format Codes](https://docs.python.org/3/library/datetime.html#strftime-and-strptime-format-codes)
- [Python 官方文件：random](https://docs.python.org/3/library/random.html)
- [Python 官方文件：os](https://docs.python.org/3/library/os.html)
- [Python 官方文件：os.path](https://docs.python.org/3/library/os.path.html)
- [Python 官方文件：sys](https://docs.python.org/3/library/sys.html)
- [Python 官方文件：io](https://docs.python.org/3/library/io.html)
- [Python 官方文件：pydoc](https://docs.python.org/3/library/pydoc.html)
