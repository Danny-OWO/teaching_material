# 第 4 章：`for` 迴圈

當重複次數已知時，通常使用 `for` 迴圈。

## 1. 基本寫法

```cpp
for (int i = 0; i < 5; i++) {
    cout << i << '\n';
}
```

這段程式會輸出 `0` 到 `4`。

`for` 的三個部分分別是：

1. `int i = 0`：建立並設定起始值。
2. `i < 5`：每次執行前檢查條件。
3. `i++`：每次執行後更新變數。

## 2. 指定範圍

輸出 `5` 到 `8`：

```cpp
for (int i = 5; i <= 8; i++) {
    cout << i << ' ';
}
```

倒數並每次減少 2：

```cpp
for (int i = 10; i > 0; i -= 2) {
    cout << i << ' ';
}
```

## 3. 累加

計算 `1 + 2 + ... + n`：

```cpp
int n;
cin >> n;

int sum = 0;
for (int i = 1; i <= n; i++) {
    sum += i;
}
cout << sum << '\n';
```

累加器要在迴圈前設定初始值。做乘積時，初始值通常設為 `1`。

## 4. 巢狀迴圈

迴圈裡可以放另一個迴圈：

```cpp
for (int row = 1; row <= 3; row++) {
    for (int col = 1; col <= 4; col++) {
        cout << '*';
    }
    cout << '\n';
}
```

這會輸出一個 3 列、4 欄的長方形。

## 5. 計數與乘積

計算一組資料中有幾個 `0`：

```cpp
int n, zeroCount = 0;
cin >> n;

for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x == 0) {
        zeroCount++;
    }
}
```

計算階乘 `n!`：

```cpp
long long factorial = 1;
for (int i = 2; i <= n; i++) {
    factorial *= i;
}
```

求和從 `0` 開始，求乘積從 `1` 開始。

## 6. 選擇迴圈範圍

| 需求 | 常用寫法 |
|---|---|
| 重複 `n` 次 | `for (int i = 0; i < n; i++)` |
| 從 `1` 到 `n` | `for (int i = 1; i <= n; i++)` |
| 從 `n` 倒數到 `1` | `for (int i = n; i >= 1; i--)` |
| 每次增加 `step` | `for (int i = start; i <= end; i += step)` |

寫迴圈前先確認起點、終點是否包含，以及每次要增加多少。
