# 第 7 章：File I/O 與檔案系統

本章整理 `open`、`close`、`read`、`write`、append mode、檔案存在檢查、刪除及 `with` statement，並介紹 `io`、`os` 與 `os.path`。

## 1. `open()` 與模式

```python
file = open("notes.txt", "r", encoding="utf-8")
content = file.read()
file.close()
```

| mode | 意義 | 檔案不存在 | 原內容 |
|---|---|---|---|
| `r` | 讀取文字 | `FileNotFoundError` | 保留 |
| `w` | 寫入文字 | 建立 | **清空** |
| `a` | 附加文字 | 建立 | 保留，寫到末端 |
| `x` | 僅建立新檔 | 建立 | 已存在則 `FileExistsError` |
| `b` | binary 修飾 | 依主模式 | 讀寫 bytes |
| `+` | 讀寫修飾 | 依主模式 | 依主模式 |

`"w"` 會先清空既有檔案內容。

## 2. 優先使用 `with`

```python
with open("notes.txt", "r", encoding="utf-8") as file:
    content = file.read()

# 離開 block 後，即使途中發生例外也會關閉檔案
print(file.closed)  # True
```

`close()` 可手動關閉檔案；`with` 能在離開 block 時自動關閉。

## 3. 讀取方法

```python
with open("data.txt", encoding="utf-8") as file:
    all_text = file.read()      # 剩餘內容全部讀成 str
```

```python
with open("data.txt", encoding="utf-8") as file:
    first = file.readline()     # 一行，通常保留結尾 \n
    lines = file.readlines()   # 剩餘各行組成 list[str]
```

最常見且省記憶體的逐行讀取：

```python
with open("data.txt", encoding="utf-8") as file:
    for line in file:
        print(line.rstrip("\n"))
```

File cursor 會移動。第一次 `read()` 到檔尾後，第二次通常得到空字串；可用 `seek(0)` 回到開頭。

## 4. 寫入與附加

```python
with open("report.txt", "w", encoding="utf-8") as file:
    count = file.write("first line\n")  # 回傳寫入字元數
    file.writelines(["A\n", "B\n"])
```

`write()` 需要字串；`write(123)` 是 `TypeError`。`writelines()` 不會自動替每一項加換行。

```python
with open("report.txt", "a", encoding="utf-8") as file:
    file.write("appended\n")
```

## 5. 檢查檔案存在

```python
import os.path

if os.path.exists("report.txt"):
    print("path exists")

if os.path.isfile("report.txt"):
    print("regular file")

if os.path.isdir("output"):
    print("directory")
```

`exists()` 只說路徑存在，不保證它是檔案。

## 6. 組合路徑

```python
import os

path = os.path.join("output", "report.txt")
absolute = os.path.abspath(path)
folder = os.path.dirname(path)
name = os.path.basename(path)
```

`os.path.join()` 會依作業系統使用正確的路徑格式。

## 7. 刪除檔案

```python
import os

path = "old.txt"
if os.path.isfile(path):
    os.remove(path)
```

刪除不存在的檔案會發生 `FileNotFoundError`；`os.remove()` 不能用來刪除目錄。刪除前應確認目標路徑。

## 8. `io` module

`io` 定義 Python 的 stream 類別。`StringIO` 可建立記憶體中的文字 stream：

```python
import io

buffer = io.StringIO()
buffer.write("hello")
buffer.write(" world")
buffer.seek(0)
print(buffer.read())  # hello world
buffer.close()
```

`StringIO` 的介面像文字檔，但資料留在記憶體，適合測試 I/O 邏輯。

## 9. 整合範例

```python
import os.path


def append_score(path, name, score):
    """Append one CSV-like score record to path."""
    with open(path, "a", encoding="utf-8") as file:
        file.write(f"{name},{score}\n")


def read_scores(path):
    """Return score records; return an empty list when path is absent."""
    if not os.path.isfile(path):
        return []

    records = []
    with open(path, encoding="utf-8") as file:
        for line in file:
            name, score_text = line.rstrip("\n").split(",")
            records.append((name, int(score_text)))
    return records
```

## 10. 本章考點檢核與練習

- 能預測各 mode 對不存在／已存在檔案的影響。
- 分清 `read`、`readline`、`readlines` 與逐行 iteration。
- 記得 `write` 不會自動換行，`writelines` 也不會。
- 能用 `with` 確保 close。
- 能用 `os.path.exists` / `isfile` 與 `os.remove`。
- 能說明 file cursor 與 `seek(0)`。

練習：寫一個 log analyzer，檔案不存在時顯示錯誤；存在時逐行計算包含 `ERROR` 的行數，將摘要 append 到另一個檔案，不可讀完整檔案進記憶體。

## 11. 來源

- [Python 官方教學：Reading and Writing Files](https://docs.python.org/3/tutorial/inputoutput.html#reading-and-writing-files)
- [Python 官方文件：os.path](https://docs.python.org/3/library/os.path.html)
- [Python 官方文件：io](https://docs.python.org/3/library/io.html)

