# DFS 深度優先搜尋

假設你和朋友去逛夜市，朋友說要把每一條巷子都逛完。你的策略很簡單：先挑一條走到底，遇到死路就退回最近的岔路，換一條還沒逛過的路。

朋友問你為什麼不先把入口附近逛完。**哪來那麼多要求**，而這正是 **DFS（Depth First Search，深度優先搜尋）**。

---

## 1. 其實你已經見過 DFS：走訪一棵樹

先看這棵樹，每次都先處理左邊：

```text
        8
       / \
      4   12
     / \
    2   6
```

從 `8` 出發，先去 `4`，再去 `2`。`2` 處理完，回到 `4` 處理 `6`；整個左邊都處理完，才回到 `8` 去找 `12`。

所以「第一次拜訪」的順序是 `8 → 4 → 2 → 6 → 12`。

```python
tree = [8, 4, 12, 2, 6]

def dfs(i):
    if i >= len(tree) or tree[i] is None:
        return

    print(tree[i], end=" ")
    dfs(2 * i + 1)
    dfs(2 * i + 2)

dfs(0)
print()
```
### 遞迴回來以後，到底從哪裡繼續？

卡住時不要急著背程式，先盯著這兩行：

```text
dfs(左邊)
dfs(右邊)
```

第一行必須整個執行完，才會執行第二行。`dfs(4)` 還沒結束，`dfs(8)` 就會等著，不會自己偷跑去 `12`。

而 **`return` 結束的是目前這一次函式呼叫。回到上一層後，會從呼叫位置的下一行繼續。** 

### 同一棵樹，改成求總和

走訪順序懂了以後，我們只換「每個節點要做什麼」。
例如求總和：

```python
tree = [8, 4, 12, 2, 6, 10, 14, 1, None, 5, None, None, 11, 13, None]

def dfs(i):
    if i >= len(tree) or tree[i] is None:
        return 0
    return tree[i] + dfs(2 * i + 1) + dfs(2 * i + 2)

print(dfs(0))  # 86
```

這次 `dfs(i)` 的意思是「回傳以 `i` 為根的整棵子樹總和」。自己加上左邊，再加上右邊，就完成了。

---

## 2. 沒有樹，也可以 DFS：兩格密碼

現在你忘記了置物櫃密碼，只記得有兩格，每格都是 `1、2、3`，數字可以重複。先別急著拆櫃子，我們只有九種可能。

用兩層迴圈很好寫，但如果密碼長度改成輸入的 `m` 呢？總不能輸入 100，就現場幫它寫 100 層迴圈。

我們把「填下一格」交給下一次函式呼叫：

```python
n = 3
m = 2

def dfs(path):
    if len(path) == m:
        print(*path)
        return

    for x in range(1, n + 1):
        dfs(path + [x])

dfs([])
```

```text
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
```

`path` 是已經填好的部分。`dfs([1])` 的任務就是：**前面已經填了 1，請把剩下的格子填完，列出所有答案。**

把選擇畫出來，就會發現樹一直都在，只是不用真的建立節點：

```text
                         []
             /            |            \
           [1]           [2]           [3]
         /  |  \       /  |  \       /  |  \
       11  12  13     21  22  23     31  32  33
```

這棵樹叫做 **搜尋樹**。一層填一格，走到底就是一組答案。

先回答三個問題，程式就有骨架了：

| 問題 | 這題的答案 |
|---|---|
| 目前狀態是什麼？ | 已填好的 `path` |
| 下一步可以做什麼？ | 接上 `1、2、3` 的其中一個 |
| 什麼時候結束？ | `len(path) == m`，印出答案並返回 |

這題是**允許重複的序列列舉**，共有 $n^m$ 組答案。先不要和「每個數字只能用一次」的排列混在一起。

---

## 3. 回溯：借走的東西，要還回去

剛剛的 `path + [x]` 會建立新串列，所以上一層的 `path` 不會被改到。另一種寫法是大家共用同一個串列，每次加進去，做完再拿出來：

```python
n = 3
m = 2

def dfs(path):
    if len(path) == m:
        print(*path)
        return

    for x in range(1, n + 1):
        path.append(x)   # 做出選擇
        dfs(path)        # 把剩下的格子填完
        path.pop()       # 撤銷剛才的選擇

dfs([])
```

輸出和上一節完全相同。但這次有個非常重要的動作：**恢復現場**，也就是 **回溯（Backtracking）**。

假設第一格已經選了 `1`，現在要試第二格：

| 動作 | `path` |
|---|---|
| 進入這一層 | `[1]` |
| `append(1)` | `[1, 1]` |
| 呼叫下一層，印出答案，返回 | `[1, 1]` |
| `pop()` | `[1]` |
| 下一輪 `append(2)` | `[1, 2]` |

`return` 會回到上一層，**卻不會自動把串列變回原樣**。忘記 `pop()`，上一條路的選擇就會污染下一條路。程式沒有失憶功能，你改過的東西它真的會記得。

### 要把答案存起來時，再小心一件事

如果不想直接印出，而是放進 `answers`，請在完成答案時使用 `answers.append(path.copy())`。

`answers.append(path)` 存的是同一個串列的參考。之後 `path.pop()`，你以為已經存好的答案也會跟著變。`path[:]` 和 `path.copy()` 在這些只放整數的例子裡都可以使用。

也不是所有東西都要手動還原。例如下一節的 `index + 1` 是傳給下一層的新整數，呼叫回來後，這一層的 `index` 沒有因此變大。

---

## 4. 子集合：每個東西，選或不選

現在桌上有 `[1, 2, 3]` 三張不同的卡片，你可以拿任意張，也可以一張都不拿。問題從「下一格填什麼」變成「這一張要不要拿」。

因此 `dfs(index, path)` 表示：**前面的卡片都決定好了，現在輪到索引 `index`。**

```python
nums = [1, 2, 3]

def dfs(index, path):
    if index == len(nums):
        print(path)
        return

    path.append(nums[index])
    dfs(index + 1, path)  # 選這張
    path.pop()

    dfs(index + 1, path)  # 不選這張

dfs(0, [])
```

```text
[1, 2, 3]
[1, 2]
[1, 3]
[1]
[2, 3]
[2]
[3]
[]
```

三張卡片，每張都有兩種決定，因此有 $2^3 = 8$ 個子集合。**空集合也是答案**，因為「全部都不選」是一種合法決定。

這裡不能用 `len(path) == len(nums)` 當成唯一的終止條件，因為你可能不拿任何一張。決策做完了沒有，要看 `index`；選了幾張，才是看 `len(path)`。

---

## 5. 組合：這次規定只拿兩張

從 `1、2、3、4` 中選兩個，不考慮順序。`[1, 2]` 和 `[2, 1]` 是同一組；換隻手拿，不會突然多出一組答案。

可以沿用「選或不選」，限制最後恰好選兩張。不過 Daan 還提供另一種更直接的寫法：**只往後選**。

```python
nums = [1, 2, 3, 4]
k = 2

def dfs(start, path):
    if len(path) == k:
        print(path)
        return

    for i in range(start, len(nums)):
        path.append(nums[i])
        dfs(i + 1, path)
        path.pop()

dfs(0, [])
```

```text
[1, 2]
[1, 3]
[1, 4]
[2, 3]
[2, 4]
[3, 4]
```

`start` 是**這一層可以開始選的索引**。選了索引 `i`，下一層就從 `i + 1` 開始，因此不能再選自己，也不能回頭選前面的卡片。

重點不是背 `i + 1`，而是知道它強迫索引遞增。每一組只會以一種順序被產生，所以不需要事後刪掉 `[2, 1]`。

### 還能順手剪掉不可能的路

假設還差三張，但後面只剩兩張，就不用再找了。這叫做 **剪枝（Pruning）**：已經能證明走不出答案的分支，提早停止。

在上面程式的完成條件後、`for` 迴圈前，可以加入：

```python
    if len(nums) - start < k - len(path):
        return
```

左邊是剩下的卡片數，右邊是還缺的卡片數。它不會漏掉答案，只會省下不可能成功的搜尋。

---

## 6. 排列：換位置，就是不同答案

同樣是 `1、2、3`，現在要排成一列，每個數字恰好用一次。這時 `[1, 2, 3]` 和 `[2, 1, 3]` 就是不同答案。

如果繼續用 `start` 限制只能往後選，第一格放 `2` 後就永遠放不了 `1`，答案會少掉。所以每層都要重新看所有位置，再用 `used` 記錄**目前這條路**用了誰。

```python
nums = [1, 2, 3]
used = [False] * len(nums)

def dfs(path):
    if len(path) == len(nums):
        print(path)
        return

    for i in range(len(nums)):
        if used[i]:
            continue

        used[i] = True
        path.append(nums[i])
        dfs(path)
        path.pop()
        used[i] = False

dfs([])
```

```text
[1, 2, 3]
[1, 3, 2]
[2, 1, 3]
[2, 3, 1]
[3, 1, 2]
[3, 2, 1]
```

`used[i]` 記的是**索引 i 這個元素是否已放進目前答案**。搜尋 `[1, 2, 3]` 完成後，`3` 必須釋放，才可以拿去組成別的排列。

這次做了兩種修改：`path.append(...)` 和 `used[i] = True`，回來也要恢復兩種狀態。只還一半，不能算有還。

### 先停一下：三種題型差在哪？

以下先假設輸入的元素互不相同：

| 題型 | 每層在決定什麼？ | 關鍵控制 |
|---|---|---|
| 可重複序列 | 下一格放哪個值？ | 每層試所有值，長度到 `m` 結束 |
| 子集合 | 這個元素選不選？ | `index + 1`，所有元素決定完才結束 |
| 組合 | 下一個要選哪個元素？ | 從 `start` 往後選，下一層用 `i + 1` |
| 排列 | 下一個位置放誰？ | 每層試所有索引，用 `used` 防止重用 |

不要看到 DFS 就先打 `used`。**先搞清楚什麼算同一個答案，再決定怎麼搜尋。**

---

## 7. 換個外皮：電話按鍵與字母大小寫

Daan 的電話按鍵例子，其實就是第二節的密碼，只是每格能選的東西不同。例如 `"23"`：第一格選 `abc`，第二格選 `def`。

```python
letters = {"2": "abc", "3": "def", "4": "ghi", "5": "jkl",
           "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
digits = "23"  # 本例輸入只包含 2 到 9
answers = []

def dfs(index, path):
    if index == len(digits):
        answers.append("".join(path))
        return

    for ch in letters[digits[index]]:
        path.append(ch)
        dfs(index + 1, path)
        path.pop()

if digits:
    dfs(0, [])
print(answers)
```

輸出是 `['ad', 'ae', 'af', 'bd', 'be', 'bf', 'cd', 'ce', 'cf']`。空輸入則保留空的答案串列。

字母大小寫的例子也一樣：給 `"a1b2"`，遇到英文字母就分成小寫、大寫兩條路；遇到數字就只有原樣保留一條路。

```python
s = "a1b2"  # 本例只考慮英文字母與數字
answers = []

def dfs(index, path):
    if index == len(s):
        answers.append("".join(path))
        return

    ch = s[index]
    choices = [ch.lower(), ch.upper()] if ch.isalpha() else [ch]
    for choice in choices:
        path.append(choice)
        dfs(index + 1, path)
        path.pop()

dfs(0, [])
print(answers)  # ['a1b2', 'a1B2', 'A1b2', 'A1B2']
```

這裡每個字元都必須處理，不需要再用 `for i in range(start, ...)` 枚舉下一個索引。**下一步的位置已經確定了，只有填什麼還沒確定。**

---

## 8. 組合加總：下一層到底傳 i，還是 i + 1？

給定互不相同的正整數 `[2, 3, 6, 7]`，找出總和為 `7` 的組合，這次允許同一個數字重複使用。

答案是 `[2, 2, 3]` 和 `[7]`。我們仍然不要 `[3, 2, 2]`，所以仍使用 `start`；但選了 `2` 之後還可以再選 `2`，下一層就要從 **`i`** 開始。

```python
candidates = [2, 3, 6, 7]
target = 7
answers = []

def dfs(start, path, total):
    if total == target:
        answers.append(path.copy())
        return
    if total > target:
        return

    for i in range(start, len(candidates)):
        path.append(candidates[i])
        dfs(i, path, total + candidates[i])
        path.pop()

dfs(0, [], 0)
print(answers)  # [[2, 2, 3], [7]]
```

`total` 跟著狀態傳下去，就不用每次重新計算 `sum(path)`。

**這裡的剪枝和終止性依賴候選數都是正整數。** 超過目標就不可能降回來，而且每次選擇都會讓總和增加。若能無限選 `0`，遞迴可能永遠不會結束；若有負數，超過目標也不代表沒救。

| 規則 | 選了索引 `i` 以後 |
|---|---|
| 同一個元素只能用一次 | `dfs(i + 1, ...)` |
| 同一個元素可以重複用 | `dfs(i, ...)` |

Daan 的「從 1 到 9 選 `k` 個不同數字，總和為目標」則結合兩個條件：用 `i + 1` 防止重用，選滿 `k` 個時只收集總和正確的答案，接著立刻返回。

---

## 9. 有重複元素：不是最後丟進 set 就沒事了

假設輸入是 `[1, 1, 2, 5]`，每個位置只能用一次，要湊出總和 `3`。兩個 `1` 的位置不同，但選出來的 `[1, 2]` 算同一個答案。

先排序，讓相同數字相鄰，再讓**同一層的相同選擇只做一次**：

```python
candidates = sorted([1, 1, 2, 5])
target = 3
answers = []

def dfs(start, path, total):
    if total == target:
        answers.append(path.copy())
        return

    for i in range(start, len(candidates)):
        if i > start and candidates[i] == candidates[i - 1]:
            continue
        if total + candidates[i] > target:
            break  # 已排序，而且都是正整數，後面的也不用試

        path.append(candidates[i])
        dfs(i + 1, path, total + candidates[i])
        path.pop()

dfs(0, [], 0)
print(answers)  # [[1, 2]]
```

為什麼是 `i > start`，不是 `i > 0`？把兩個 `1` 想成 `1A、1B`：

- 在根這一層，試過 `1A` 後，再從 `1B` 出發會產生相同的答案，所以跳過。
- 但選了 `1A` 進入下一層後，`1B` 是第一個候選，仍然可以選。否則合法的 `[1, 1]` 也會被你刪掉。

**同層去重，並不是整條路上不准有重複值。** Daan 的 Subsets II 也能沿用這個判斷，只要每次進入函式就收集目前的 `path.copy()`，而不必等到某個指定總和。

### 排列有重複值怎麼辦？

排列沒有 `start`，所以不能直接搬上一個條件。以 `[1, 1, 2]` 為例：排序後，規定相同值的元素按原索引順序使用。

```python
nums = sorted([1, 1, 2])
used = [False] * len(nums)
answers = []

def dfs(path):
    if len(path) == len(nums):
        answers.append(path.copy())
        return

    for i in range(len(nums)):
        if used[i]:
            continue
        if i > 0 and nums[i] == nums[i - 1] and not used[i - 1]:
            continue

        used[i] = True
        path.append(nums[i])
        dfs(path)
        path.pop()
        used[i] = False

dfs([])
print(answers)  # [[1, 1, 2], [1, 2, 1], [2, 1, 1]]
```

如果前一個 `1` 還沒用，現在先用後一個 `1` 只是交換兩個相同元素的身分，會重複。前一個 `1` 已經在路徑裡時，後一個當然可以接上去。

---

## 10. 回到真的地圖：迷宮走得到嗎？

前面是在搜尋「選擇」，現在搜尋「位置」。Daan 的迷宮使用 `0` 表示通路、`1` 表示牆壁，從左上走到右下，只能上下左右移動。

```text
0 0 1
1 0 0
0 1 0
```

`dfs(r, c)` 的任務是：從這個位置繼續找，能不能抵達終點？走成功就回傳 `True`，而且要一路傳回最外層。

```python
grid = [[0, 0, 1], [1, 0, 0], [0, 1, 0]]
rows, cols = len(grid), len(grid[0])
visited = [[False] * cols for _ in range(rows)]
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def dfs(r, c):
    if not (0 <= r < rows and 0 <= c < cols):
        return False
    if grid[r][c] == 1 or visited[r][c]:
        return False

    visited[r][c] = True
    if (r, c) == (rows - 1, cols - 1):
        return True

    for dr, dc in directions:
        if dfs(r + dr, c + dc):
            return True
    return False

print("yes" if dfs(0, 0) else "no")  # yes
```

先判斷能不能走，再判斷是不是終點。否則終點明明是牆壁，也可能被誤判成功。`visited` 則阻止你在兩格之間無限來回。

### 為什麼這次 visited 不改回 False？

因為這題只問**是否可達**，每個位置探索一次就夠了。若每次返回都取消標記，就可能反覆搜尋同一區域。

| 狀態 | 代表什麼？ | 返回後恢復嗎？ |
|---|---|---|
| 排列的 `used[i]` | 這個元素在目前答案中 | 要，其他答案還要用 |
| 迷宮可達性的 `visited[r][c]` | 這格已經拜訪過 | 不用，避免重複探索 |
| 列舉所有不重複經過格子的路徑時的標記 | 這格在目前路徑中 | 要，其他路徑仍可經過 |

所以「DFS 前改了什麼，回來全部改回去」不是通則。**要不要恢復，取決於它記的是目前這條路，還是整次搜尋的歷史。**

另外，DFS 找到的第一條路不保證最短。這一節只解決走不走得到。

### 不用遞迴：自己維護 stack

遞迴利用函式呼叫堆疊，手動寫則可以用串列的 `append()`、`pop()` 實作 stack。最後放進去的位置會最先被取出。

```python
def can_reach(grid):
    rows, cols = len(grid), len(grid[0])
    if grid[0][0] == 1 or grid[rows - 1][cols - 1] == 1:
        return False

    visited = [[False] * cols for _ in range(rows)]
    stack = [(0, 0)]
    visited[0][0] = True

    while stack:
        r, c = stack.pop()
        if (r, c) == (rows - 1, cols - 1):
            return True

        for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nr, nc = r + dr, c + dc
            if not (0 <= nr < rows and 0 <= nc < cols):
                continue
            if grid[nr][nc] == 1 or visited[nr][nc]:
                continue
            visited[nr][nc] = True
            stack.append((nr, nc))

    return False

print("yes" if can_reach([[0, 0, 1], [1, 0, 0], [0, 1, 0]]) else "no")
```

兩種寫法都能判斷可達性，但拜訪順序不一定相同。這裡在加入 stack 時就標記，避免同一格重複入堆疊。

迷宮大時，遞迴深度可能達到格子數。Python 的遞迴深度有限，單純把限制調得很大也不保證安全；這時可以使用上面的 stack 寫法。

---

## 11. DFS 不會讓暴力搜尋突然變便宜

DFS 幫我們有系統地探索可能性，卻不會消除那些可能性。輸出一百萬組答案，至少就得處理那一百萬組。

下面假設元素互異，並把輸出或複製每一組答案的成本算進去；空間欄不包含保存全部答案的空間。

| 題型 | 答案數量／搜尋規模 | 時間複雜度 | 額外空間 |
|---|---|---|---|
| 樹的走訪 | $N$ 個節點 | $O(N)$ | $O(H)$，`H` 是樹高 |
| `n` 種值填 `m` 格 | $n^m$ 組 | $O(m n^m)$ | $O(m)$，使用回溯版 |
| `n` 個元素的子集合 | $2^n$ 組 | $O(n 2^n)$ | $O(n)$ |
| `n` 個元素的全排列 | $n!$ 組 | $O(n \cdot n!)$ | $O(n)$ |
| `R × C` 迷宮可達性 | 每格最多拜訪一次 | $O(RC)$ | $O(RC)$ |

組合恰選 `k` 個時有 $\binom{n}{k}$ 個答案，光輸出就需要 $\Omega(k\binom{n}{k})$ 的時間，另外還要計入未完成分支的搜尋成本。第五節的剪枝能減少走不完的分支。

如果要把答案全部存進 `answers`，空間也要再加上答案總大小。不要只看到遞迴最多 `n` 層，就把保存一大堆答案的空間忘了。

---

## 12. 接著怎麼練：把 Daan 的範例串起來

同題的重複寫法先不用每一份都背。建議照下面順序，先自己描述狀態，再動手寫；題名沿用原 notebook，這裡列的是練習重點。

| 順序 | 範例 | 練習重點 |
|---|---|---|
| 1 | 二元樹走訪、節點總和 | 看懂呼叫與返回，替 `dfs` 定義明確任務 |
| 2 | 兩格密碼 | 比較 `path + [x]` 與 `append → dfs → pop` |
| 3 | Letter Combinations of a Phone Number、Letter Case Permutation | 每一層的選項可以不同 |
| 4 | Subsets | 選或不選，包含空集合 |
| 5 | 選 `k` 個數、Combination Sum III | `start`、固定個數、總和條件 |
| 6 | 排列生成、Permutations | `used` 與回溯 |
| 7 | Combination Sum、Combination Sum II | 重複使用和重複答案是兩回事 |
| 8 | Subsets II、Permutations II | 排序後，區分同層去重與路徑內重用 |
| 9 | Sum of All Subset XOR Totals | 把目前 XOR 值當參數，不必每次重算整條路 |
| 10 | 迷宮可達性 | 座標、邊界、牆壁、`visited`、stack |
| 11 | 樹的前序編碼、Sum It Up、校運代表隊 | 狀態設計、輸入格式與多個限制一起處理 |

### 進階範例先抓住這幾個重點

**樹的前序編碼**：Daan 的例子用 `0` 表示空節點，非零偶數有兩個子位置，奇數有三個。每次讀一個值，再遞迴讀完它的子樹；若節點與父節點都存在，就累加兩者差的絕對值。使用共用讀取索引或迭代器，避免反覆 `pop(0)` 搬動整個串列。父節點不存在可以用 `None` 明確表示。

**Sum It Up**：套用不能重用元素的組合搜尋，再處理相同值與題目要求的輸出順序。先檢查去重依賴的排序條件，不能只看到 `continue` 就照抄。

**校運代表隊**：從小到大挑編號，用技能集合記錄已選技能，用各班計數記錄班級人數限制。下一層從 `i + 1` 開始，返回時把技能、班級計數和答案一起恢復。若要找第 `t` 組，找到後必須把「已找到」的訊號一路傳回，不能只在最深的一層 `return`。

原稿中的八皇后、Apple Division 與 Grid Path Description 可以留到後續挑戰，分別練習位置衝突、兩組分配與更強的路徑剪枝。Knuth's Permutation 則另外留意指定的生成順序，不一定能直接用一般排列模板交差。

最後請試著不看程式，回答這四件事：**目前決定到哪裡？下一步有哪些選擇？什麼時候收集答案或停止？返回後哪些狀態要恢復？**

能說清楚這四件事，再來寫 `dfs`。不然函式雖然叫深度優先，理解可能還停在表面。
