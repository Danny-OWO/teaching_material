# DFS 深度優先搜尋

DFS，全名為 **Depth First Search（深度優先搜尋）**。

在正式介紹 DFS 之前，先來看看一個熟悉的東西。

假設我們有一棵二元樹：

```text
        5
       / \
      3   8
     / \ / \
    1  4 7  9
```

如果使用前序拜訪（Preorder）：

```cpp
void preorder(Node* cur)
{
    if (cur == nullptr)
    {
        return;
    }

    cout << cur->num << " ";

    preorder(cur->l);
    preorder(cur->r);
}
```

```cpp
def preorder(cur)
{
    if (cur == None)
    {
        return;
    }

    cout << cur.num << " ";

    preorder(cur.l);
    preorder(cur.r);
}
```

會得到：

```text
5 3 1 4 8 7 9
```

其實到了這裡，你已經偷偷使用過 **DFS** 了。

---

## 1. DFS 是什麼？

**深度優先搜尋** 就是 DFS

所以什麼優先?~~~

**深度**


DFS 的概念其實非常單純：

> **能繼續往下走，就繼續往下走；走不下去，就退回上一個地方，換一條路繼續走。**

例如：

```text
        A
       / \
      B   C
     / \
    D   E
```

從 `A` 出發。

DFS 不會先把 `B`、`C` 都看完，而是會先選一條路一路走到底。

例如：

```text
A → B → D
```

`D` 已經沒有地方可以繼續走了，因此回到 `B`：

```text
A → B → D
        ↑
        回去
```

接著走另外一條路：

```text
B → E
```

最後才回到 `A`，前往 `C`。

因此其中一種 DFS 順序會是：

```text
A → B → D → E → C
```

這就是「深度優先」的意思。

---

## 2. DFS 的基本結構

DFS 並沒有一個所有題目都完全相同的固定寫法。

不過我們可以先觀察它最基本的結構：

```cpp
void dfs(目前狀態)
{
    // 處理目前狀態

    for (每一個下一步)
    {
        dfs(下一個狀態);
    }
}
```

```python
def dfs(目前狀態):
    for i in range(下一步數量):
        dfs(下一個狀態)
```

你可能會在不同題目看到：

```cpp
dfs(cur);
```

```cpp
dfs(depth);
```

```cpp
dfs(r, c);
```

甚至：

```cpp
dfs(depth, start);
```

這些其實都還是 DFS。

**DFS 的參數，就是用來描述「我現在在哪個狀態」。**

---

## 3. DFS 與遞迴

DFS 經常使用 **遞迴（Recursion）** 實作。

以剛才的二元樹為例：

```cpp
void dfs(Node* cur)
{
    if (cur == nullptr)
    {
        return;
    }

    cout << cur->num << " ";

    dfs(cur->l);
    dfs(cur->r);
}
```

假設目前位於：

```text
A
```

程式遇到：

```cpp
dfs(cur->l);
```

就會進入左邊的節點。

如果左邊還有下一個節點，就會再次呼叫 DFS。

因此程式可能會像這樣：

```text
dfs(A)
    ↓
dfs(B)
    ↓
dfs(D)
```

當 `D` 沒有其他節點可以前往時，`dfs(D)` 結束。

程式就會回到：

```text
dfs(B)
```

再繼續處理其他方向。

所以遞迴本身的「進入 → 返回」機制，剛好非常適合實作 DFS。

---

# 4. dfs基本參數

例如：深度 `depth`
```cpp
vector<int> ans;

void dfs(int depth)
{
    if (depth == 3)
    {
        for (int x : ans)
        {
            cout << x << " ";
        }

        cout << '\n';
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        ans.push_back(i);

        dfs(depth + 1);

        ans.pop_back();
    }
}
```

這裡出現了一個非常重要的結構：

```cpp
ans.push_back(i);

dfs(depth + 1);

ans.pop_back();
```

也就是：

```text
做出選擇
    ↓
繼續 DFS
    ↓
撤銷選擇
```

為什麼最後需要：

```cpp
ans.pop_back();
```

假設目前：

```text
ans = [1, 2]
```

接著選擇 `3`：

```text
ans = [1, 2, 3]
```

這條路搜尋完成後，我們必須回到：

```text
ans = [1, 2]
```

才能繼續嘗試其他可能。

因此需要把剛才加入的 `3` 移除。

而這樣的手法又被稱為： **Backtracking（回溯）**

---

# 5. DFS + Backtracking

DFS 和 Backtracking 經常一起出現在搜尋問題中。

最常見的形式可以記成：

```cpp
void dfs(...)
{
    if (完成答案)
    {
        // 處理答案
        return;
    }

    for (每一個可能的選擇)
    {
        // 做出選擇

        dfs(...);

        // 撤銷選擇
    }
}
```

或者更簡單地記成：

```text
DO

DFS

UNDO
```

這是一個非常重要的 DFS 思考方式。

---

# 6. 排列

假設現在有：

```text
1 2 3
```

我們希望找出所有排列：

```text
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

我們可以利用

```cpp
bool used[4];
```

記錄某個數字是否已經使用。

```cpp
vector<int> ans;
bool used[4];

void dfs(int depth)
{
    if (depth == 3)
    {
        for (int x : ans)
        {
            cout << x << " ";
        }

        cout << '\n';
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        if (used[i])
        {
            continue;
        }

        used[i] = true;
        ans.push_back(i);

        dfs(depth + 1);

        ans.pop_back();
        used[i] = false;
    }
}
```

注意這裡的 Backtracking 不只有：

```cpp
ans.pop_back();
```

還有：

```cpp
used[i] = false;
```

因為我們在進入下一層之前修改了：

```cpp
used[i] = true;
```

搜尋結束之後，就必須把它恢復成原本的狀態。

因此可以記住：

> **DFS 前改了什麼，DFS 回來之後通常就要把它改回來。**

---

# 7. 組合

如果今天不是排列，而是組合，問題又有一點不同。

例如：

```text
從 1 2 3 4 中選擇兩個數字
```

`1 2` 和 `2 1` 對組合來說其實是同一種答案。

因此我們不希望：

```text
選 2 之後又回去選 1
```

這時候可以增加一個：

```cpp
start
```

表示下一次要從哪個位置開始選。

```cpp
vector<int> ans;

void dfs(int depth, int start)
{
    if (depth == 2)
    {
        for (int x : ans)
        {
            cout << x << " ";
        }

        cout << '\n';
        return;
    }

    for (int i = start; i <= 4; i++)
    {
        ans.push_back(i);

        dfs(depth + 1, i + 1);

        ans.pop_back();
    }
}
```

例如選擇：

```text
1
```

之後，下一層從：

```text
2
```

開始。

選擇：

```text
2
```

之後，下一層則從：

```text
3
```

開始。

因此不會重新產生：

```text
2 1
```

這種已經出現過的組合。

---

# 8. 剪枝 Pruning

DFS 很容易遇到一個問題：

> **可能性太多了。**

假設每一步都有兩種選擇，而且總共有 `N` 步。

可能的狀態數量可能接近：

$$
O(2^N)
$$

如果是在搜尋排列，甚至可能接近：

$$
O(N!)
$$

因此 DFS 很常搭配一個重要技巧：

**Pruning（剪枝）**

概念就是：

> 如果已經知道某條路不可能得到答案，就不要繼續走下去。

例如：

```cpp
void dfs(...)
{
    if (目前狀態已經不可能得到答案)
    {
        return;
    }

    // 繼續搜尋
}
```
---

# 9. Grid DFS

DFS 也很常出現在二維地圖問題。

例如：

```text
. . # .
. . # .
# . . .
. . # .
```

其中：

```text
. = 可以走
# = 不能走
```

我們希望從某個位置出發，把所有可以抵達的位置找出來。

這時 DFS 的「目前狀態」就不再是：

```cpp
depth
```

而是：

```cpp
r, c
```

代表目前所在的座標。

```cpp
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

void dfs(int r, int c)
{
    visited[r][c] = true;

    for (int d = 0; d < 4; d++)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (nr < 0 || nr >= R || nc < 0 || nc >= C)
        {
            continue;
        }

        if (grid[nr][nc] == '#')
        {
            continue;
        }

        if (visited[nr][nc])
        {
            continue;
        }

        dfs(nr, nc);
    }
}
```

這裡的：

```cpp
visited[r][c]
```

代表：

> 這個位置是否已經拜訪過。

如果沒有 `visited`，可能會發生：

```text
A → B → A → B → A → B → ...
```

不斷在兩個位置之間來回。

因此在 Grid 或 Graph 的 DFS 中，`visited` 是非常常見的工具。

---
# 10. DFS 到底在做什麼？

看到這裡，你可能已經看過很多不同版本：

```cpp
dfs(cur);
```

```cpp
dfs(depth);
```

```cpp
dfs(depth, start);
```

```cpp
dfs(r, c);
```

但它們其實都在做同一件事情：

> **描述目前狀態，選擇一個下一步，然後繼續往深處搜尋。**

可以把 DFS 想成：

```text
目前狀態
   │
   ├── 下一種可能
   │      │
   │      └── DFS
   │
   ├── 下一種可能
   │      │
   │      └── DFS
   │
   └── 下一種可能
          │
          └── DFS
```

因此寫 DFS 時，可以先問自己幾個問題：

1. **我的「目前狀態」需要用什麼表示？**
2. **目前有哪些選擇？**
3. **什麼時候代表找到答案？**
4. **哪些狀態不能繼續？**
5. **DFS 回來之後，有沒有東西需要恢復？**

如果這幾個問題都能回答，通常 DFS 的架構也就差不多出來了。

---

# 11. 題目練習

[**c130.00574 - Sum It Up**](https://zerojudge.tw/ShowProblem?problemid=c130)
[**d324.00750 - 8 Queens Chess Problem**](https://zerojudge.tw/ShowProblem?problemid=d324)
[**d115.數字包牌**](https://zerojudge.tw/ShowProblem?problemid=d115)
[**s181.3. 校運代表隊**](https://zerojudge.tw/ShowProblem?problemid=s181)
[**Apple Division**](https://cses.fi/problemset/task/1623)
[**Chessboard and Queens**](https://cses.fi/problemset/task/1624)
[**Grid Path Description**](https://cses.fi/problemset/task/1625)
