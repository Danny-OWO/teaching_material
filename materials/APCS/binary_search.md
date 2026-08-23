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

## 7. C++ 二分搜工具

很好，這種東西很明顯有人刻過，沒理由要我們每次都自己寫。  
這時，我們就能利用到 C++ 的 Binary Search 工具。

使用前記得：
```cpp
#include <algorithm>
```

* 1. 利用 `binary_search()` 來尋找元素

```cpp
vector<int> a = {1, 3, 5, 7, 9};

if (binary_search(a.begin(), a.end(), 5))
{
    cout << "Found!";
}
else
{
    cout << "Not Found!";
}
```

`binary_search()` 只會告訴你：

```text
有找到 → true
沒找到 → false
```

---

* 2. `lower_bound()`：找第一個 `>= target` 的位置

```cpp
vector<int> a = {1, 3, 3, 3, 5, 7};

auto it = lower_bound(a.begin(), a.end(), 3);
```

如果想取得 index 並且取值：

```cpp
int index = lower_bound(a.begin(), a.end(), 3) - a.begin();
cout << index;
cout << *it << endl;
```

> 如果沒有人符合?

```cpp
vector<int> a = {1, 3, 5, 7};
auto it = lower_bound(a.begin(), a.end(), 8);
int pos = lower_bound(a.begin(), a.end(), 8) - a.begin();
```

```text
it = a.end()
pos = 4
```

* 3. `upper_bound()`：找第一個 `> target` 的位置

```cpp
vector<int> a = {1, 3, 3, 3, 5, 7};

auto it = lower_bound(a.begin(), a.end(), 3);
int pos = upper_bound(a.begin(), a.end(), 3) - a.begin();

cout << *it << endl;
cout << pos << endl;
```

```text
5
4
```



---

* 4. 特殊技巧：計算某個數字出現幾次

這是 `lower_bound()` 和 `upper_bound()` 非常常見的組合。

```cpp
vector<int> a = {1, 2, 2, 2, 4, 5};

int count =
    upper_bound(a.begin(), a.end(), 2)
    - lower_bound(a.begin(), a.end(), 2);

cout << count;
```

輸出：

```text
3
```

因為：

```text
upper_bound - lower_bound
```

剛好就是這個數字所佔的區間長度。

---



* 5. 最常用整理

| 工具 | 找什麼 |
|---|---|
| `binary_search()` | target 是否存在 |
| `lower_bound()` | 第一個 `>= target` |
| `upper_bound()` | 第一個 `> target` |

## 8. Python 二分搜工具

很好，Python 當然也有人幫我們刻過了，沒理由要我們每次都自己寫。  
Python 裡可以使用 `bisect` 來進行 Binary Search。

使用前記得：

```python
import bisect
```

---

* 1. 利用 `bisect_left()` 來尋找元素

Python 沒有直接對應 C++ `binary_search()` 的函式，但我們可以利用 `bisect_left()` 很簡單地做到。

```python
a = [1, 3, 5, 7, 9]
target = 5

pos = bisect.bisect_left(a, target)

if pos < len(a) and a[pos] == target:
    print("Found!")
else:
    print("Not Found!")
```

`bisect_left()` 會告訴我們：

```text
第一個 >= target 的位置
```

所以只要再檢查那個位置是不是 `target`，就可以知道有沒有找到。

---

* 2. `bisect_left()`：找第一個 `>= target` 的位置

```python
a = [1, 3, 3, 3, 5, 7]

pos = bisect.bisect_left(a, 3)

print(pos)
print(a[pos])
```

輸出：

```text
1
3
```

> 如果沒有人符合？

```python
a = [1, 3, 5, 7]

pos = bisect.bisect_left(a, 8)

print(pos)
```

輸出：

```text
4
```

因為沒有任何元素 `>= 8`，所以會回傳：

```python
len(a)
```
我們便可以以此判斷是否有沒找到的情況
---

* 3. `bisect_right()`：找第一個 `> target` 的位置

```python
a = [1, 3, 3, 3, 5, 7]

pos = bisect.bisect_right(a, 3)

print(pos)
print(a[pos])
```

輸出：

```text
4
5
```

因為：

```text
[1, 3, 3, 3, 5, 7]
             ^
             第一個 > 3
```

所以：

```text
pos = 4
a[pos] = 5
```

---

* 4. 特殊技巧：計算某個數字出現幾次

這是 `bisect_left()` 和 `bisect_right()` 非常常見的組合。

```python
a = [1, 2, 2, 2, 4, 5]

count = bisect.bisect_right(a, 2) - bisect.bisect_left(a, 2)

print(count)
```

輸出：

```text
3
```

因為：

```text
bisect_right - bisect_left
```

剛好就是這個數字所佔的區間長度。

---

* 5. 最常用整理

| C++ | Python | 找什麼 |
|---|---|---|
| `binary_search()` | `bisect_left()` + 判斷 | target 是否存在 |
| `lower_bound()` | `bisect_left()` | 第一個 `>= target` |
| `upper_bound()` | `bisect_right()` | 第一個 `> target` |



## 9. binary_search 練習題目

二分搜通常不太會獨立出題，只會是一個好用工具。
那我知道你 **超級想要練習**

那就...
```text
Given two integers n and m, create a sorted list containing all integers from 1 to n, where m is the target value.

Find m using both:
- Linear search with O(n) time complexity
- Binary search with O(log n) time complexity

Use Python's time module to measure and compare the execution time of the two approaches.
```

```text
Test case:
n = 1000000
m = 894003
```

```python
import datetime
import bisect

n = int(input())
m = int(input())

lst = [i for i in range(1, n + 1)]

# Linear Search
linear_time_start = datetime.datetime.now()

for x in lst:
    if x == m:
        break

linear_time_end = datetime.datetime.now()


# Binary Search
binary_time_start = datetime.datetime.now()

pos = bisect.bisect_left(lst, m)

binary_time_end = datetime.datetime.now()


# Calculate execution time
linear_time = linear_time_end - linear_time_start
binary_time = binary_time_end - binary_time_start

print("Linear Search:", linear_time)
print("Binary Search:", binary_time)

```

測試結果

```text
Linear Search: 0:00:00.020378
Binary Search: 0:00:00.000009
```

### 二分搜題目
* [**f581.3. 圓環出口**](https://zerojudge.tw/ShowProblem?problemid=f581)


### 二分搜尋樹 (這不該是這一章的)
* [**a265.紅黑樹**](https://zerojudge.tw/ShowProblem?problemid=a265)


### 利用 binary_search 否則 TLE
* [**i401.3. 雷射測試**](https://zerojudge.tw/ShowProblem?problemid=i401)