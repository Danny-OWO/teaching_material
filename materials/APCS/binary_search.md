# 二分搜尋 binary_search

這個比喻是來自我資工啟蒙課程之一的**CS50**的課程內，如果你是高中生想要做學習歷程的自主學習，我蠻推薦的。


給你一本電話簿，裡面有成千上萬的人名以及電話號碼。還記得嗎，Sam 借走了你心愛的玩偶 (高松燈)

<img src="./resources/tomolin.jpg" width="700">

你想打電話給 Sam 叫他趕緊打消和你的娃娃組一輩子樂團的幻想，所以你埋頭苦找，想要在電話簿理翻到 Sam 的電話。

## 1. 搜尋?

厚厚的一本書，你打算...
從第一頁翻吧!

```text
["Amy", "Android", "Burgur", "Caleven", ....]
```

從頭找感覺有點累，翻了三頁你就不想找了。
聰明的你想說，那我從後面找!

```text
[...., "Witch", "X-ray", "Yeee", "Zebra"]
```

你可能會問我這些都是什麼名字，**你別管**。
總而言之，Sam不知道在第幾頁，你快哭了，完全找不到，亂翻也怕剛好錯過，看來要出事了。

## 2. 二分搜尋

好，這時候老天派了個天使下來，把你的電話簿斯成一半。然後給了你有 Sam 那一半的電話簿。
欸開心爆了，但你還是不想一個一個找。

你綁架了天使，無止盡地叫他一直撕下沒有 Sam 的那一半。
最後你很快的找到了Sam。

具體多快呢? 我們假設有100000筆人名，且 Sam 是第80803個。
* 從前面開始找，你要看：**80803**個
* 從後面開始找，你要看：**19198**個
* 不斷撕來找呢？你只要看：**14**次
```text
目標：第 80803 筆

第  1 次：看第 50000 筆 → Sam 在後面
第  2 次：看第 75000 筆 → Sam 在後面
第  3 次：看第 87500 筆 → Sam 在前面
第  4 次：看第 81250 筆 → Sam 在前面
第  5 次：看第 78125 筆 → Sam 在後面
第  6 次：看第 79687 筆 → Sam 在後面
第  7 次：看第 80468 筆 → Sam 在後面
第  8 次：看第 80859 筆 → Sam 在前面
第  9 次：看第 80663 筆 → Sam 在後面
第 10 次：看第 80761 筆 → Sam 在後面
第 11 次：看第 80810 筆 → Sam 在前面
第 12 次：看第 80785 筆 → Sam 在後面
第 13 次：看第 80797 筆 → Sam 在後面
第 14 次：看第 80803 筆 → 找到了！
```

這樣的搜尋正是：**二分搜尋法**

## 3. 二分搜尋的條件

天使可以很正確的把電話簿不斷地撕下沒有 Sam 的那一頁，正是因為：**那一本電話簿是排序過的**。
二分搜尋法最重要的便是只能用在排序過的資料情況下，否則你無法很肯定的撕下另外一半。

## 4. 二分搜尋法演示

在實作二分搜尋法時，有以下三個重要位置。

* left = 目前範圍的最左側
* right = 目前範圍的最右側
* middle = 目前範圍的中間

比如說：

```text
lst = [0, 1, 2, 3, 4, 5, ... , 99, 100]
```

我們想要找到 `68` 的話：

```text
left = 0 | right = 100 | middle = 50
```

middle 算法：**$(0+100)/2 = 50$**

由於 `lst[50] < 68`，代表 `68` 只可能出現在 middle 的右邊，因此我們需要往右邊繼續找。

```text
left = 51 | right = 100 | middle = 75
```

middle 算法：**$(51+100)/2 = 75$**

由於 `lst[75] > 68`，代表 `68` 只可能出現在 middle 的左邊，因此我們需要往左邊繼續找。

```text
left = 51 | right = 74 | middle = 62
```

middle 算法：**$(51+74)/2 = 62.5$**

因為 index 必須是整數，所以無條件捨去得到 `62`。

由於 `lst[62] < 68`，我們需要往右邊繼續找。

```text
left = 63 | right = 74 | middle = 68
```

middle 算法：**$(63+74)/2 = 68.5$**

無條件捨去得到 `68`。

這時：

```text
lst[68] == 68
```

成功找到 `68`！

---

所以我們可以發現，每次判斷完 `middle` 後：

- 如果 `lst[middle] == target`：找到答案
- 如果 `lst[middle] < target`：往右邊找，`left = middle + 1`
- 如果 `lst[middle] > target`：往左邊找，`right = middle - 1`

也就是說，每搜尋一次，我們都可以直接排除掉**大約一半的資料**。

## 5. 手刻二分搜 (C++)
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ll target;
    cin >> target;

    vector<ll> lst = {1, 2, 3, 4, 5, 6, 7, 8}; // 排序好的資料結構

    ll left = 0;
    ll right = lst.size() - 1;

    while (left <= right)
    {
        ll middle = (left + right) / 2;

        if (lst[middle] == target)
        {
            cout << "FIND!" << endl;
            return 0;
        }
        else if (lst[middle] > target)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }

    cout << "Either too big or too small" << endl;
}
```

## 6. 手刻二分搜 (python)
```python
target = int(input())

lst = [1, 2, 3, 4, 5, 6, 7, 8]  # 排序好的資料結構

left = 0
right = len(lst) - 1

while left <= right:
    middle = (left + right) // 2

    if lst[middle] == target:
        print("FIND!")
        break
    elif lst[middle] > target:
        right = middle - 1
    else:
        left = middle + 1
else:
    print("Either too big or too small")
```

## 7. 我用 C++ && 我不想刻

很好，這種東西很明顯有人刻過，沒理由要我們每次都自己寫。  
這時，我們就能利用到 C++ 的 Binary Search 工具。

> **注意：不管使用哪一種工具，資料都必須先排序好！**

C++ 的 `<algorithm>` 中，有這個：

```cpp
binary_search()
```

它的特點是：可以協助我們確認

> **這個元素到底在不在裡面？**

例如：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> lst = {1, 3, 5, 7, 9, 11};

    if (binary_search(lst.begin(), lst.end(), 7))
    {
        cout << "FIND!" << endl;
    }
    else
    {
        cout << "NOT FOUND!" << endl;
    }
}
```

`binary_search()` 會回傳一個 `bool`：

```text
找到     → true
找不到   → false
```

所以我們可以直接把它放進 `if` 裡面。

基本格式：

```cpp
binary_search(開始位置, 結束位置, 要找的東西);
```

對 `vector` 來說通常就是：

```cpp
binary_search(lst.begin(), lst.end(), target);
```

## 8. 我用 python and 我不想刻

Python 的工具不像 C++ `binary_search()` 那麼直觀。

Python 提供的是：

```python
bisect
```

使用之前需要：

```python
import bisect
```

其中最常用的是：

```python
bisect.bisect_left()
```

例如：

```python
import bisect

lst = [1, 3, 5, 7, 9, 11]

pos = bisect.bisect_left(lst, 7)

print(pos)
```

輸出：

```text
3
```

因為：

```text
 index
   ↓
0  1  2  3  4   5
1  3  5  7  9  11
         ↑
```

`7` 位於 index `3`。

---

`bisect_left()` 並不是在直接找該數字，而是

> **「如果要把這個數字插進去，最左邊可以插在哪裡？」**

例如：

```python
import bisect

lst = [1, 3, 5, 7, 9, 11]

pos = bisect.bisect_left(lst, 6)

print(pos)
```

一樣會得到一個位置：

```text
3
```

`6` 雖然不在裡面，但是如果我們要插入 `6`：

```text
[1, 3, 5, 6, 7, 9, 11]
          ↑
```

它就應該被放在 index = `3` 的位置。

因此如果我們真的想判斷 `target` 存不存在，可以寫：

```python
import bisect

lst = [1, 3, 5, 7, 9, 11]
target = 7

pos = bisect.bisect_left(lst, target)

if pos < len(lst) and lst[pos] == target:
    print("FIND!")
else:
    print("NOT FOUND!")
```

---

痾對，你可能會想要問：

**Python 為什麼不直接去找數字是否存在？**

而這就要講到接下來兩個非常重要的東西：

```text
lower_bound
upper_bound
```