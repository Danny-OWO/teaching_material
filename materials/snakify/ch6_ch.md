# 第 6 章：`while` 迴圈

當重複次數無法事先確定時，通常使用 `while`。

## 1. 基本寫法

```cpp
int i = 1;
while (i <= 5) {
    cout << i << '\n';
    i++;
}
```

每次執行前都會先檢查條件。要記得在迴圈中改變相關變數，否則可能形成無限迴圈。

## 2. 讀取一串資料

以下程式持續讀入整數，遇到 `0` 時停止：

```cpp
int x;
int sum = 0;

cin >> x;
while (x != 0) {
    sum += x;
    cin >> x;
}

cout << sum << '\n';
```

這裡的 `0` 是結束標記，不會加入總和。

## 3. `break` 與 `continue`

- `break` 立即離開最內層迴圈。
- `continue` 跳過本次剩餘內容，直接進入下一次迴圈。

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) continue;
    if (i == 9) break;
    cout << i << ' ';
}
```

如果能用清楚的迴圈條件完成，就不必特地使用 `break`。

## 4. 常見處理方式

讀取資料時，常會同時記錄：

- 數量：`count++`
- 總和：`sum += x`
- 最大值：當 `x > maximum` 時更新

更新的位置要放在讀取下一筆資料之前。

## 5. 處理整數的每一位

只要數字還不為 `0`，就能重複取出個位數：

```cpp
int n;
cin >> n;

int digitSum = 0;
while (n > 0) {
    digitSum += n % 10;
    n /= 10;
}
```

`n % 10` 取得最後一位，`n /= 10` 刪除最後一位。

## 6. 尋找最小因數

```cpp
int n;
cin >> n;

int divisor = 2;
while (n % divisor != 0) {
    divisor++;
}
cout << divisor << '\n';
```

每次迴圈都讓候選答案更接近目標，找到能整除 `n` 的數字就停止。

## 7. 相鄰資料與 Fibonacci 數列

有些題目需要同時保留「前一個值」與「目前值」：

```cpp
long long previous = 0;
long long current = 1;

for (int i = 0; i < n; i++) {
    cout << previous << ' ';
    long long next = previous + current;
    previous = current;
    current = next;
}
```

先算出 `next` 再更新兩個變數，可以避免舊值太早被覆蓋。
