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
