# 第 10 章：集合 `set`

`set` 用來儲存不重複的元素，並且會依大小排序。使用前要引入 `<set>`。

## 1. 建立與加入元素

```cpp
set<int> numbers = {3, 1, 2, 3};
numbers.insert(5);
```

集合中只會保留一個 `3`。`numbers.size()` 可以取得元素數量。

## 2. 查找元素

```cpp
if (numbers.count(2) > 0) {
    cout << "found\n";
}
```

在 `set` 中，`count(value)` 的結果只會是 `0` 或 `1`。

## 3. 刪除與走訪

```cpp
numbers.erase(3);

for (int value : numbers) {
    cout << value << ' ';
}
```

刪除不存在的值不會造成錯誤。走訪 `set` 時，元素會依排序後的順序出現。

## 4. 常見用途

計算輸入中有幾種不同的數字：

```cpp
int n;
cin >> n;

set<int> seen;
for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    seen.insert(x);
}

cout << seen.size() << '\n';
```

`set` 很適合用來去除重複值，或檢查某個值是否曾經出現。

## 5. 常用操作整理

| 寫法 | 功能 |
|---|---|
| `s.insert(x)` | 加入 `x` |
| `s.erase(x)` | 刪除 `x` |
| `s.count(x)` | 檢查 `x` 是否存在 |
| `s.find(x)` | 尋找 `x` 的位置 |
| `s.size()` | 元素數量 |
| `s.empty()` | 是否為空 |
| `s.clear()` | 刪除所有元素 |

`insert` 也會告訴我們是否真的加入了新元素：

```cpp
auto result = seen.insert(x);
if (result.second) {
    cout << "first time\n";
} else {
    cout << "seen before\n";
}
```

## 6. 聯集、交集與差集

為了保持寫法簡單，可以用迴圈完成集合運算。

```cpp
set<int> a = {1, 2, 3};
set<int> b = {2, 3, 4};

set<int> unionSet = a;
for (int x : b) {
    unionSet.insert(x);
}

set<int> intersection;
for (int x : a) {
    if (b.count(x)) {
        intersection.insert(x);
    }
}

set<int> difference;
for (int x : a) {
    if (!b.count(x)) {
        difference.insert(x);
    }
}
```

- 聯集：至少出現在其中一個集合。
- 交集：同時出現在兩個集合。
- 差集：出現在 `a`，但沒有出現在 `b`。
