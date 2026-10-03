# 第 8 章：函式與遞迴

函式把一段工作取名並重複使用，讓程式更容易閱讀。

## 1. 定義函式

```cpp
int maximum(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}
```

第一個 `int` 是回傳型別，`maximum` 是函式名稱，小括號內是參數。

```cpp
int answer = maximum(8, 3);
```

`return` 會結束函式並送回結果。

## 2. 不回傳數值的函式

使用 `void` 表示沒有回傳值：

```cpp
void printLine(int length)
{
    for (int i = 0; i < length; i++) {
        cout << '-';
    }
    cout << '\n';
}
```

函式內宣告的變數是區域變數，只能在該函式中使用。

## 3. 傳值與參考

一般參數是複製一份值，修改它不會影響原本的變數。加上 `&` 可以讓函式修改原本的值。

```cpp
void addOne(int& x)
{
    x++;
}
```

若只想避免複製、但不允許修改，可使用 `const` 參考：

```cpp
int length(const string& text)
{
    return text.size();
}
```

## 4. 遞迴

函式可以呼叫自己，這稱為遞迴。

```cpp
long long factorial(int n)
{
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

遞迴一定要有停止條件。若呼叫層數太深，可能耗盡記憶體；能用簡單迴圈完成時，迴圈通常更合適。

## 5. 將 `vector` 傳入函式

只讀取資料時，使用 `const` 參考：

```cpp
int sum(const vector<int>& values)
{
    int result = 0;
    for (int value : values) {
        result += value;
    }
    return result;
}
```

需要修改內容時，移除 `const`：

```cpp
void doubleAll(vector<int>& values)
{
    for (int& value : values) {
        value *= 2;
    }
}
```

## 6. 遞迴的組成

每個遞迴函式都要回答兩個問題：

1. 最簡單的情況如何直接得到答案？
2. 如何把問題縮小，讓它逐步接近最簡單的情況？

例如快速計算整數次方：

```cpp
long long power(long long a, int n)
{
    if (n == 0) {
        return 1;
    }

    long long half = power(a, n / 2);
    if (n % 2 == 0) {
        return half * half;
    }
    return half * half * a;
}
```

每次把 `n` 除以 `2`，問題會快速縮小。
