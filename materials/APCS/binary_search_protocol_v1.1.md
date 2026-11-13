# 二分搜尋：不要把 Sam 留在被撕掉的那一半

> 適合對象：已經會陣列、索引、條件判斷與 `while` 迴圈，準備開始學習基礎演算法的 APCS 學生。

讀完這篇，你應該能做到四件事：

- 判斷一份資料能不能使用二分搜尋。
- 用 `left`、`middle`、`right` 追蹤每一輪搜尋範圍。
- 正確寫出 C++ 與 Python 的二分搜尋，包含「找不到」的情況。
- 分辨「有沒有 target」、「第一個 `>= target`」與「第一個 `> target`」。

---

## 1. Sam 又把你的娃娃借走了

你有一本依姓名排序的電話簿，Sam 的電話就在裡面。

<img src="./resources/tomolin.jpg" width="700" alt="高松燈">

Sam 借走了你心愛的娃娃，還打算拿它組一輩子的樂團。你決定打電話阻止他，但電話簿厚得像一本可以拿來防身的資料結構課本。

最直覺的方式，是從第一筆開始找：

```text
Amy, Android, Burger, Caleven, ..., Sam, ..., Zebra
```

如果共有 `100000` 筆資料，而 Sam 在第 `80803` 筆，從頭找最多可能看 `80803` 次。這叫做 **線性搜尋（linear search）**：每次只排除一筆資料，最壞時間複雜度是 $O(n)$。

但這本電話簿已經依姓名排序。我們可以直接翻到中間：

- 中間是 `Mia`，`Sam` 按字母順序在 `Mia` 後面。
- 因此前半本不可能有 `Sam`，整半本都能排除。
- 在剩下的一半再翻中間，重複相同判斷。

這就是 **二分搜尋（binary search）**：每次比較後，排除目前搜尋範圍的大約一半。

!!! question "電話簿可以亂撕嗎？"
    如果電話簿沒有排序，翻到中間看到 `Mia`，我們還能斷定 Sam 一定在右半邊嗎？

    不能。沒有順序，就沒有理由丟掉任何一半。

---

## 2. 從電話簿換回陣列

電話簿和陣列看起來差很多，但剛才的每個動作都有明確對應：

| 電話簿故事 | 演算法概念 |
|---|---|
| 依姓名排序的電話簿 | 已排序的陣列 |
| 目前還留在手上的頁面 | 尚未排除的搜尋區間 |
| 翻到中間一頁 | 檢查 `middle` |
| 比較 Sam 和中間姓名的順序 | 比較 `target` 和 `a[middle]` |
| 撕掉確定沒有 Sam 的一半 | 排除不可能包含答案的區間 |
| 所有頁面都被排除 | 搜尋失敗 |

### 電話簿沒有真的被撕掉

現實中不必真的撕電話簿；陣列也不會因為二分搜尋而被切開或複製。我們只移動兩個邊界，記住「現在還要找哪一段」。

而且「資料有序」只是常見的充分條件。更精確地說，我們需要一個能把答案兩側可靠分開的**單調條件**。這個想法會在「二分答案」再次出現，但本篇先專心處理已排序陣列。

---

## 3. 三個角色與一條最重要的規則

假設：

```text
index:  0   1   2   3   4   5   6   7
value:  1   3   5   7   9  11  13  15
```

我們想找 `target = 11`。

- `left`：目前搜尋區間最左側。
- `right`：目前搜尋區間最右側。
- `middle`：這一輪要檢查的位置。

本篇手刻版本採用**閉區間**：

```text
[left, right]
```

左右兩端都還是候選答案。因此，只要 `left <= right`，搜尋區間就還沒有空。

### 搜尋區間不變量

在每一輪開始時，我們都維持以下承諾：

> 如果 `target` 存在，那麼它一定在 `a[left:right + 1]` 裡。

這句話叫做 **迴圈不變量（loop invariant）**。它不是裝飾用的理論名詞，而是判斷邊界該怎麼移動的裁判。

---

## 4. 手動追蹤一次

一開始：

```text
left = 0, right = 7
middle = (0 + 7) // 2 = 3
a[middle] = 7
```

因為 `7 < 11`，`middle` 和它左邊的值都不可能是答案：

```text
left = middle + 1 = 4
```

第二輪：

```text
left = 4, right = 7
middle = (4 + 7) // 2 = 5
a[middle] = 11
```

找到答案，回傳索引 `5`。

| 輪次 | `left` | `middle` | `right` | `a[middle]` | 決定 |
|---:|---:|---:|---:|---:|---|
| 1 | 0 | 3 | 7 | 7 | 太小，令 `left = 4` |
| 2 | 4 | 5 | 7 | 11 | 找到索引 5 |

### 為什麼是 `middle + 1`？

當 `a[middle] < target` 時，`middle` 已經親自證明自己不是答案。如果只寫：

```python
left = middle
```

在只剩兩個元素時，`middle` 可能一直等於 `left`，搜尋範圍不再縮小，迴圈就卡住。寫成 `middle + 1` 才會把已經檢查過的位置排除。

同理，當 `a[middle] > target` 時，要寫：

```python
right = middle - 1
```

!!! warning "二分搜尋最常見的死法"
    `+1`、`-1` 不是祖傳咒語，而是配合閉區間 `[left, right]` 的結果。若改用半開區間 `[left, right)`，更新方式與迴圈條件也必須一起改，不能剪一半程式碼再靠信仰拼回去。

---

## 5. 三種比較結果

每一輪只需要判斷：

| 條件 | 意義 | 更新 |
|---|---|---|
| `a[middle] == target` | 找到答案 | 回傳 `middle` |
| `a[middle] < target` | 中間值太小 | `left = middle + 1` |
| `a[middle] > target` | 中間值太大 | `right = middle - 1` |

如果最後變成：

```text
left > right
```

代表搜尋區間已經是空集合，`target` 不在陣列中。

### 理解檢查

在下列陣列尋找 `8`：

```text
[1, 3, 5, 7, 9, 11, 13]
```

請先自己填完，再展開答案。

<details markdown="1">
<summary>展開答案</summary>

| 輪次 | `left` | `middle` | `right` | `a[middle]` | 決定 |
|---:|---:|---:|---:|---:|---|
| 1 | 0 | 3 | 6 | 7 | `left = 4` |
| 2 | 4 | 5 | 6 | 11 | `right = 4` |
| 3 | 4 | 4 | 4 | 9 | `right = 3` |

最後 `left = 4 > right = 3`，所以找不到 `8`。

</details>

---

## 6. 手刻精確值搜尋

先寫成語言無關的 pseudocode：

```text
binary_search(a, target):
    left = 0
    right = length(a) - 1

    while left <= right:
        middle = left + (right - left) // 2

        if a[middle] == target:
            return middle
        else if a[middle] < target:
            left = middle + 1
        else:
            right = middle - 1

    return NOT_FOUND
```

中點使用：

```text
left + (right - left) // 2
```

它和 `(left + right) // 2` 數學上相等，但在固定寬度整數的語言中能避免 `left + right` 溢位。以 APCS 常見陣列大小而言通常不會撞到，但養成安全習慣不收學費。

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<int>& a, int target) {
    int left = 0;
    int right = static_cast<int>(a.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (a[middle] == target) {
            return middle;
        }
        if (a[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

int main() {
    vector<int> a = {1, 3, 5, 7, 9, 11, 13, 15};

    cout << binarySearch(a, 11) << '\n';  // 5
    cout << binarySearch(a, 8) << '\n';   // -1
}
```

### Python

```python
def binary_search(a, target):
    left = 0
    right = len(a) - 1

    while left <= right:
        middle = left + (right - left) // 2

        if a[middle] == target:
            return middle
        if a[middle] < target:
            left = middle + 1
        else:
            right = middle - 1

    return -1


a = [1, 3, 5, 7, 9, 11, 13, 15]
print(binary_search(a, 11))  # 5
print(binary_search(a, 8))   # -1
```

!!! note "空陣列為什麼也安全？"
    空陣列會得到 `right = -1`。一開始 `left <= right` 就是 `0 <= -1`，條件為假，因此不會存取不存在的 `a[0]`。

---

## 7. 用極端案例攻擊自己的程式

「範例有過」和「程式正確」中間，通常隔著好幾隻 off-by-one 怪獸。至少檢查：

| 測試 | 陣列 | target | 預期 |
|---|---|---:|---|
| 空陣列 | `[]` | 3 | `-1` |
| 單元素且找到 | `[3]` | 3 | `0` |
| 單元素但找不到 | `[3]` | 2 | `-1` |
| 第一個元素 | `[1, 3, 5]` | 1 | `0` |
| 最後一個元素 | `[1, 3, 5]` | 5 | `2` |
| 小於所有元素 | `[1, 3, 5]` | 0 | `-1` |
| 大於所有元素 | `[1, 3, 5]` | 9 | `-1` |
| 重複值 | `[1, 3, 3, 3, 5]` | 3 | 任一個值為 3 的索引 |

注意最後一列：一般 binary search 只保證找到**某一個** `3`，不保證最左邊或最右邊。要指定邊界，就要換問題。

---

## 8. 為什麼是 O(log n)？

假設一開始有 $n$ 個候選元素。每次比較後，最多只留下大約一半：

```text
n → n/2 → n/4 → n/8 → ... → 1
```

做了 $k$ 次後，剩下約：

$$
\frac{n}{2^k}
$$

當它縮小到 `1` 時：

$$
\frac{n}{2^k} \le 1
\quad\Rightarrow\quad
n \le 2^k
\quad\Rightarrow\quad
k \ge \log_2 n
$$

因此二分搜尋的時間複雜度是 $O(\log n)$，迭代版本額外空間是 $O(1)$。

| 資料量 | 線性搜尋最壞比較次數 | 二分搜尋約需比較次數 |
|---:|---:|---:|
| 8 | 8 | 3–4 |
| 1,024 | 1,024 | 約 10 |
| 1,000,000 | 1,000,000 | 約 20 |

如果資料量翻倍，線性搜尋最壞工作量也大約翻倍；二分搜尋通常只多一輪。這才是它真正離譜的地方。

!!! warning "別拿一次計時當複雜度證明"
    單次執行時間會受到直譯器、編譯器、快取與作業系統影響。計時可以觀察現象，但 $O(\log n)$ 的依據是候選範圍每輪減半，不是某一次剛好跑出 `0.000009` 秒。

---

## 9. 三個長得像、問題卻不同的搜尋

對排序陣列：

```text
a = [1, 3, 3, 3, 5, 7]
```

我們可能問三種問題：

1. `3` 存不存在？
2. 第一個 `>= 3` 的位置在哪裡？
3. 第一個 `> 3` 的位置在哪裡？

答案分別是：

```text
存在
第一個 >= 3：index 1
第一個 >  3：index 4
```

後兩種搜尋把陣列切成兩區：

```text
lower bound of 3
[ values < 3 | values >= 3 ]
               ^ index 1

upper bound of 3
[ values <= 3 | values > 3 ]
                ^ index 4
```

所以 `3` 出現的次數就是：

```text
upper_bound(3) - lower_bound(3) = 4 - 1 = 3
```

這裡回傳的是**插入位置**。如果沒有符合的元素，位置可能等於陣列長度；那是合法答案，但不是合法索引。

---

## 10. C++ 標準函式庫

需要：

```cpp
#include <algorithm>
```

### `binary_search()`：只問存不存在

```cpp
vector<int> a = {1, 3, 3, 3, 5, 7};

if (binary_search(a.begin(), a.end(), 3)) {
    cout << "Found\n";
}
```

它只回傳 `true` 或 `false`，不回傳索引。

### `lower_bound()`：第一個 `>= target`

```cpp
auto lower = lower_bound(a.begin(), a.end(), 3);
int lowerIndex = static_cast<int>(lower - a.begin());

cout << lowerIndex << '\n';  // 1
```

### `upper_bound()`：第一個 `> target`

```cpp
auto upper = upper_bound(a.begin(), a.end(), 3);
int upperIndex = static_cast<int>(upper - a.begin());

cout << upperIndex << '\n';  // 4
```

### 千萬別直接解參考 `end()`

```cpp
auto it = lower_bound(a.begin(), a.end(), 100);

if (it == a.end()) {
    cout << "沒有任何元素 >= 100\n";
} else {
    cout << *it << '\n';
}
```

`a.end()` 指向最後一個元素的下一格，不能使用 `*it` 取值。

---

## 11. Python `bisect`

需要：

```python
import bisect
```

Python 的 `bisect` 主要找**插入位置**，沒有直接對應 C++ `binary_search()` 的函式。

```python
import bisect

a = [1, 3, 3, 3, 5, 7]
target = 3

left_pos = bisect.bisect_left(a, target)
right_pos = bisect.bisect_right(a, target)

print(left_pos)   # 1：第一個 >= 3
print(right_pos)  # 4：第一個 > 3
print(right_pos - left_pos)  # 3：出現次數
```

要判斷 `target` 是否真的存在，必須再檢查位置：

```python
pos = bisect.bisect_left(a, target)
found = pos < len(a) and a[pos] == target

print(found)
```

`pos < len(a)` 必須放在前面。Python 的 `and` 會短路求值；若 `pos == len(a)`，就不會繼續存取越界的 `a[pos]`。

### 工具對照

| 問題 | C++ | Python |
|---|---|---|
| target 是否存在 | `binary_search()` | `bisect_left()` 後再檢查 |
| 第一個 `>= target` | `lower_bound()` | `bisect_left()` |
| 第一個 `> target` | `upper_bound()` | `bisect_right()` |

!!! note "插入不一定是 O(log n)"
    `bisect` 找位置是 $O(\log n)$；但 Python list 在中間插入元素仍需搬動後方資料，所以 `insort` 的整體插入成本是 $O(n)$。找到停車位很快，不代表把後面所有車往後挪也很快。

---

## 12. 常見錯誤診療室

### 症狀一：沒排序就直接二分

```text
[8, 1, 6, 3, 9]
```

看到中間值 `6` 小於 `8`，不能推論 `8` 一定在右邊。資料沒有順序，排除哪一邊都沒有證據。

### 症狀二：搜尋範圍沒有縮小

```python
left = middle       # 危險
right = middle      # 搭配閉區間也危險
```

若 `middle` 已經被檢查且不是答案，就必須排除它。

### 症狀三：迴圈條件寫成 `left < right`

在閉區間版本中，`left == right` 代表還有最後一個候選值。跳過它，就可能漏掉答案。

### 症狀四：把插入位置當成一定存在

`lower_bound` 與 `bisect_left` 即使找不到 target，也會回傳一個合法插入位置。必須另外檢查該位置是否仍在範圍內，以及值是否相等。

### 症狀五：把二分搜尋和二元搜尋樹當成同一件事

二分搜尋是在可隨機存取的有序範圍上不斷排除一半；二元搜尋樹則是具有左右子樹關係的資料結構。兩者名字很像，但儲存方式、操作方法與適用題型並不相同。

---

## 13. 練習：從會抄到會判斷

### A. 快速理解檢查

1. 為什麼二分搜尋需要有序資料或其他單調條件？
2. 在閉區間版本中，為什麼迴圈是 `left <= right`？
3. `lower_bound` 回傳 `end()` 是否代表函式出錯？
4. 一般二分搜尋在重複值中，是否保證找到最左邊那一個？

<details markdown="1">
<summary>展開參考答案</summary>

1. 比較中間值後，必須有足夠資訊安全排除其中一邊。
2. `left == right` 時仍有一個候選元素。
3. 不是；它表示沒有元素符合 `>= target`，插入位置在尾端。
4. 不保證，只保證找到某個相等位置。

</details>

### B. Code tracing

對下列資料尋找 `target = 2`，列出每一輪的 `left`、`middle`、`right`：

```text
[2, 4, 6, 8, 10, 12]
```

接著把 target 改成 `11`，再追蹤一次。不要執行程式；先讓自己的腦袋當一次很慢但有尊嚴的 CPU。

### C. Debugging

下面的程式可能無限迴圈。請找出原因並修正：

```python
def broken_search(a, target):
    left = 0
    right = len(a) - 1

    while left <= right:
        middle = (left + right) // 2
        if a[middle] == target:
            return middle
        if a[middle] < target:
            left = middle
        else:
            right = middle

    return -1
```

### D. 邊界搜尋

給定排序陣列與 `target`，輸出 `target` 出現的次數。分別使用：

- C++ 的 `lower_bound()`、`upper_bound()`。
- Python 的 `bisect_left()`、`bisect_right()`。

### E. 遷移題：資料先排序值得嗎？

你有一份尚未排序的 `n` 筆資料：

- 情境甲：只查詢一次。
- 情境乙：接下來要查詢十萬次，而且資料不再改變。

比較「每次線性搜尋」與「先排序，再二分搜尋」的總成本。請說明哪種策略在什麼情況下比較合理，而不是看到 binary search 就條件反射先 `sort()`。

---

## 14. 章末速查

```text
前提：資料有序，或判斷條件具有單調性

閉區間：[left, right]
繼續條件：left <= right
中點：left + (right - left) // 2

a[middle] == target → 找到
a[middle] <  target → left  = middle + 1
a[middle] >  target → right = middle - 1

精確搜尋：O(log n)
迭代額外空間：O(1)

lower bound：第一個 >= target
upper bound：第一個 >  target
target 次數：upper bound - lower bound
```

二分搜尋的核心從來不是「取中間」而已。真正的核心是：

> 每做一次判斷，都能證明某一大段範圍不可能有答案，然後毫不留情地把它排除。

這次請確定 Sam 不在你撕掉的那一半。
