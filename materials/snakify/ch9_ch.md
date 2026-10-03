# 第 9 章：二維 `vector`

二維 `vector` 可以表示表格或矩陣。資料以「列、欄」的順序存取。

## 1. 建立二維資料

```cpp
vector<vector<int>> table = {
    {1, 2, 3},
    {4, 5, 6}
};

cout << table[0][2];  // 3
```

`table[i][j]` 表示第 `i` 列、第 `j` 欄的元素，索引都從 `0` 開始。

## 2. 建立固定大小的表格

建立 `n` 列、`m` 欄，初始值都是 `0`：

```cpp
int n, m;
cin >> n >> m;

vector<vector<int>> a(n, vector<int>(m, 0));
```

## 3. 輸入與輸出

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cin >> a[i][j];
    }
}

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cout << a[i][j] << ' ';
    }
    cout << '\n';
}
```

外層迴圈處理列，內層迴圈處理該列的每一欄。

## 4. 對角線

正方形表格中：

- 主對角線：`i == j`
- 主對角線上方：`i < j`
- 主對角線下方：`i > j`
- 副對角線：`i + j == n - 1`

```cpp
for (int i = 0; i < n; i++) {
    a[i][i] = 1;
}
```

這段程式把主對角線上的元素設為 `1`。

## 5. 列數與欄數

```cpp
int rows = a.size();
int columns = a.empty() ? 0 : a[0].size();
```

先檢查 `a.empty()`，才不會在空表格中存取 `a[0]`。

也可以直接走訪每一列：

```cpp
for (const vector<int>& row : a) {
    for (int value : row) {
        cout << value << ' ';
    }
    cout << '\n';
}
```

## 6. 交換兩欄

```cpp
int firstColumn, secondColumn;
cin >> firstColumn >> secondColumn;

for (int i = 0; i < n; i++) {
    swap(a[i][firstColumn], a[i][secondColumn]);
}
```

每一列都交換相同的兩個欄位置。

## 7. 矩陣乘法

若 `a` 是 `n × m`，`b` 是 `m × k`，結果會是 `n × k`：

```cpp
vector<vector<long long>> result(n, vector<long long>(k, 0));

for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
        for (int t = 0; t < m; t++) {
            result[i][j] += 1LL * a[i][t] * b[t][j];
        }
    }
}
```

三個索引分別表示結果的列、結果的欄，以及相乘後加總的位置。
