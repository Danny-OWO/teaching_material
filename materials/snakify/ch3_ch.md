# 第 3 章：條件判斷

條件判斷讓程式依照不同情況執行不同程式碼。

## 1. `if` 與 `else`

```cpp
int x;
cin >> x;

if (x >= 0) {
    cout << x << '\n';
} else {
    cout << -x << '\n';
}
```

小括號內是條件。條件成立時執行 `if` 區塊，否則執行 `else` 區塊。若條件不成立時不需要做事，可以省略 `else`。

## 2. 比較運算子

| 運算子 | 意思 |
|---|---|
| `==` | 等於 |
| `!=` | 不等於 |
| `<` | 小於 |
| `>` | 大於 |
| `<=` | 小於或等於 |
| `>=` | 大於或等於 |

比較的結果是 `bool`，值為 `true` 或 `false`。注意 `=` 是指定值，`==` 才是比較。

## 3. 多個條件

| 運算子 | 意思 |
|---|---|
| `&&` | 而且 |
| `||` | 或者 |
| `!` | 相反 |

```cpp
if (age >= 12 && age <= 18) {
    cout << "teenager\n";
}
```

## 4. `else if`

```cpp
if (score >= 90) {
    cout << "A\n";
} else if (score >= 80) {
    cout << "B\n";
} else {
    cout << "Keep trying\n";
}
```

條件會由上往下檢查，只執行第一個成立的區塊。

## 5. 巢狀條件

條件區塊裡可以再放一個條件。例如判斷座標位於哪個象限：

```cpp
if (x > 0) {
    if (y > 0) {
        cout << "I\n";
    } else {
        cout << "IV\n";
    }
} else {
    if (y > 0) {
        cout << "II\n";
    } else {
        cout << "III\n";
    }
}
```

若能用 `&&` 或 `else if` 寫得更清楚，就不必過度巢狀。

## 6. 常用函式與判斷技巧

引入 `<algorithm>` 後可以使用 `min`、`max` 與 `swap`：

```cpp
cout << min(a, b) << '\n';
cout << max(a, b) << '\n';
swap(a, b);
```

引入 `<cstdlib>` 後，`abs(x)` 可以取得整數的絕對值。

棋盤移動題常利用座標差：

```cpp
int dx = abs(x1 - x2);
int dy = abs(y1 - y2);

bool rook = (x1 == x2 || y1 == y2) && (dx + dy > 0);
bool bishop = (dx == dy && dx > 0);
bool king = (max(dx, dy) == 1);
bool queen = rook || bishop;
bool knight = (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
```

先把複雜條件存成有意義的 `bool` 變數，程式會更容易檢查。
