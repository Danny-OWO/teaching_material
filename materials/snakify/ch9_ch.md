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
