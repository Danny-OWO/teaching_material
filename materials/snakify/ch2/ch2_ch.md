# 第 2 章：整數與浮點數

這一章會更仔細地處理數字。C++ 不像 Python 會在執行時自動替變數決定型別；我們必須先選好 `int`、`long long`、`float` 或 `double`。這看起來比較麻煩，但也讓我們更清楚資料如何被儲存與計算。

## 1. 整數運算

整數常用 `int` 儲存；數值可能很大時，可以使用範圍更大的 `long long`。

```cpp
int a = 17;
long long population = 8000000000LL;
```

整數可以使用 `+`、`-`、`*`、`/` 和 `%`：

```cpp
cout << 17 / 3 << '\n';  // 5：商
cout << 17 % 3 << '\n';  // 2：餘數
```

在 C++ 中，兩個整數相除仍然得到整數，小數部分會被直接捨去。這和 Python 的 `/` 不同：Python 的 `17 / 3` 會得到小數，並另外使用 `17 // 3` 做整數除法；C++ 沒有 `//` 運算子，因為 `//` 是註解的開頭。

> 請先看運算元的型別，而不是接收答案的變數。`double x = 17 / 3;` 的結果仍是 `5.0`，因為右邊早已完成整數除法。

若要保留小數，至少讓其中一個運算元是浮點數：

```cpp
double x = 17.0 / 3;              // 5.66666...
double y = static_cast<double>(17) / 3;
```

### 用 `/` 與 `%` 拆解位數

對非負整數而言，`n % 10` 取得個位數，`n / 10` 去掉個位數。

```cpp
int n = 472;
int ones = n % 10;          // 2
int tens = n / 10 % 10;     // 7
int hundreds = n / 100;     // 4
```

同樣地，`n % 100` 取得最後兩位，`n / 100` 去掉最後兩位。這個技巧會用在本章的數字反轉、時鐘與金額題目。

C++ 整數有固定範圍，超出範圍不會像 Python 整數那樣自動變大。計算可能超過約 20 億時，通常應改用 `long long`；若乘法結果可能很大，運算元本身也要先轉成 `long long`。

```cpp
long long product = 1LL * a * b;
```

## 2. 浮點數

`float` 和 `double` 都能儲存小數，但通常優先使用精度較高的 `double`。

```cpp
double x;
cin >> x;
cout << x << '\n';
```

如此一來便能儲存浮點數

## 3. `<cmath>` 數學函式庫

Python 使用 `import math`；C++ 則在程式開頭引入 `<cmath>`：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x = 4.2;
    cout << ceil(x) << '\n';       // 5
    cout << ceil(1 + 3.8) << '\n'; // 5
}
```

`ceil(x)` 是大於或等於 `x` 的最小整數值；`floor(x)` 則是小於或等於 `x` 的最大整數值。

若不寫 `using namespace std;`，函式要加上 `std::`：

```cpp
double answer = std::sqrt(25.0);
```

這相當於 Python 的 `math.sqrt(25.0)`。C++ 沒有 Python 的 `from math import ceil` 語法；一般直接寫 `std::ceil`，或只在很小的作用域使用 `using std::ceil;`。

| 類別 | C++ 寫法 | 說明 |
|---|---|---|
| 取整 | `floor(x)` | 向下取整：不大於 `x` 的最大整數值 |
| 取整 | `ceil(x)` | 向上取整：不小於 `x` 的最小整數值 |
| 取整 | `round(x)` | 四捨五入；剛好在中間時往遠離 0 的方向取整 |
| 絕對值 | `abs(x)` | `x` 的絕對值 |
| 次方 | `pow(x, y)` | 計算 x 的 y 次方 |
| 根號 | `sqrt(x)` | 計算平方根 |
| 對數 | `log(x)` | 以 e 為底的自然對數 |
| 對數 | `log10(x)` | 以 10 為底的對數 |
| 三角函式 | `sin(x)` | `x` 弧度的正弦值 |
| 反三角函式 | `asin(x)` | 反正弦，回傳弧度 |
| 指數 | `exp(x)` | 計算 e 的 x 次方 |

Python 可以寫 `x ** y`，但 C++ 沒有 `**` 運算子，必須使用 `pow(x, y)`。如果只是計算整數的平方，`x * x` 通常更直接，也不會把問題繞進浮點數。

C++ 的 `log` 也沒有 Python `math.log(x, base)` 的第二個底數參數。任意底數 `b` 的對數可利用換底公式：

```cpp
double value = log(x) / log(b);
```

### π 與 e

若使用 C++20，可以引入 `<numbers>` 後使用標準常數：

```cpp
#include <numbers>

double pi = std::numbers::pi;
double e = std::numbers::e;
```

較舊的編譯環境可以用 `acos(-1.0)` 得到 π、用 `exp(1.0)` 得到 e。`M_PI` 雖然常見，卻不是所有 C++ 編譯器都保證提供。

三角函式使用的是弧度，不是角度。角度轉弧度可寫成：

```cpp
double radians = degrees * acos(-1.0) / 180.0;
```


