# 第 7 章：`vector`

`vector` 可以依需要儲存多個同型別的值。使用前要引入 `<vector>`。

## 1. 建立與存取

```cpp
vector<int> numbers = {2, 3, 5, 7};

cout << numbers[0] << '\n';       // 2
cout << numbers.size() << '\n';   // 4
numbers[1] = 10;
```

索引從 `0` 開始，最後一個索引是 `size() - 1`。

## 2. 讀取資料

```cpp
int n;
cin >> n;

vector<int> a(n);
for (int i = 0; i < n; i++) {
    cin >> a[i];
}
```

`vector<int> a(n)` 建立含有 `n` 個整數的容器。

## 3. 走訪元素

需要索引時：

```cpp
for (int i = 0; i < a.size(); i++) {
    cout << i << ": " << a[i] << '\n';
}
```

只需要元素時，可以使用範圍式迴圈：

```cpp
for (int value : a) {
    cout << value << ' ';
}
```

## 4. 新增與刪除

```cpp
vector<int> a;
a.push_back(10);
a.push_back(20);
a.pop_back();
```

`push_back` 在尾端加入元素；`pop_back` 刪除最後一個元素。不要對空的 `vector` 使用 `pop_back`。

常用函式還有：

- `a.empty()`：是否為空。
- `a.front()`：第一個元素。
- `a.back()`：最後一個元素。
- `a.clear()`：刪除所有元素。

## 5. `<algorithm>` 常用函式

這些函式使用 `[begin, end)` 範圍，也就是包含開頭、不包含結尾。

| 寫法 | 功能 |
|---|---|
| `sort(a.begin(), a.end())` | 由小到大排序 |
| `reverse(a.begin(), a.end())` | 反轉順序 |
| `count(a.begin(), a.end(), x)` | 計算 `x` 出現幾次 |
| `find(a.begin(), a.end(), x)` | 尋找 `x` |
| `min_element(a.begin(), a.end())` | 尋找最小元素的位置 |
| `max_element(a.begin(), a.end())` | 尋找最大元素的位置 |

```cpp
#include <algorithm>

sort(a.begin(), a.end());

if (!a.empty()) {
    int largest = *max_element(a.begin(), a.end());
}

if (find(a.begin(), a.end(), 7) != a.end()) {
    cout << "found\n";
}
```

`find` 找不到時會回傳 `a.end()`。`min_element` 和 `max_element` 回傳位置，前面加上 `*` 才能取得元素值。

## 6. 交換與刪除指定位置

```cpp
swap(a[i], a[j]);
a.erase(a.begin() + i);
```

刪除一段範圍：

```cpp
a.erase(a.begin() + left, a.begin() + right);
```

這會刪除索引 `[left, right)`。刪除後，後面的索引會往前移動。

## 7. 常見走訪模式

比較相鄰元素時，從索引 `1` 開始：

```cpp
for (int i = 1; i < a.size(); i++) {
    if (a[i] > a[i - 1]) {
        cout << a[i] << ' ';
    }
}
```

同時查看左右鄰居時，只走訪中間元素：

```cpp
for (int i = 1; i + 1 < a.size(); i++) {
    if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
        cout << a[i] << ' ';
    }
}
```
