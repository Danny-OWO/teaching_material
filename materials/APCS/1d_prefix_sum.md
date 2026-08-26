# 一維前綴和

對於**頻繁查詢一個區間總和**的問題，可以使用 **前綴和（Prefix Sum）**。

---

## 1. 暴力做法

假設給定一個陣列：

```text
[2, 1, 2, 3, 4]
```

現在想要查詢：

> 第 2 個位置到第 4 個位置的總和。

如果直接一個一個加：

```text
1 + 2 + 3 = 6
```

答案就是：

```text
6
```

如果區間長度為 `N`，每次查詢最壞可能需要把整個陣列掃過一次，因此一次查詢需要：

$$
O(N)
$$

如果有很多次區間查詢，整體效率就會比較差。

---

# 2. 前綴和

前綴和的概念是：

> 先記錄「從最前面到目前位置為止的總和」。

也就是：

$$
P[i] = A[1] + A[2] + \cdots + A[i]
$$

例如原本的陣列：

```text
A = [2, 1, 2, 3, 4]
```

它的前綴和陣列為：

```text
P = [2, 3, 5, 8, 12]
```

計算方式：

```text
2 = 2

2 + 1 = 3

2 + 1 + 2 = 5

2 + 1 + 2 + 3 = 8

2 + 1 + 2 + 3 + 4 = 12
```

因此：

```text
原陣列：  [2, 1, 2, 3, 4]
前綴和：  [2, 3, 5, 8, 12]
```

---

# 3. 建立 Prefix Sum

實際上我們不需要每次都重新從頭加。

因為：

$$
P[i] = P[i-1] + A[i]
$$

例如：

```text
A = [2, 1, 2, 3, 4]
```

建立前綴和：

```text
P[0] = 2
P[1] = 2 + 1 = 3
P[2] = 3 + 2 = 5
P[3] = 5 + 3 = 8
P[4] = 8 + 4 = 12
```

最後：

```text
P = [2, 3, 5, 8, 12]
```

建立整個 Prefix Sum 只需要掃過陣列一次，因此時間複雜度是：

$$
O(N)
$$

---

# 4. 使用前綴和進行區間查詢

現在回到原本的問題：

> 查詢第 2～4 個位置的總和。

原陣列：

```text
[2, 1, 2, 3, 4]
```

我們想求：

```text
1 + 2 + 3
```

如果觀察前綴和：

```text
P = [2, 3, 5, 8, 12]
```

`P[4]` 代表：

```text
第 1 個位置 ～ 第 4 個位置
2 + 1 + 2 + 3 = 8
```

但是我們不需要第 1 個位置的 `2`。

所以把它扣掉：

```text
8 - 2 = 6
```

因此：

```text
第 2 ～ 4 個位置總和 = 6
```

---

# 5. 為什麼可以用相減？

假設我們想求：

$$
[l,r]
$$

的總和。

`P[r]` 包含：

```text
A[1] + A[2] + ... + A[l-1] + A[l] + ... + A[r]
```

而 `P[l-1]` 包含：

```text
A[1] + A[2] + ... + A[l-1]
```

兩個相減：

```text
P[r] - P[l-1]
```

前面的部分就會全部被消掉，只剩下：

```text
A[l] + A[l+1] + ... + A[r]
```

所以：

$$
\boxed{sum(l,r)=P[r]-P[l-1]}
$$

---

# 6. 多留一格的寫法

實際寫程式時，通常會讓 Prefix Sum 多一格：

```text
A = [2, 1, 2, 3, 4]

P = [0, 2, 3, 5, 8, 12]
```

其中：

```text
P[0] = 0
```

接著：

```text
P[1] = 2
P[2] = 3
P[3] = 5
P[4] = 8
P[5] = 12
```

這樣做的好處是公式會非常乾淨。

例如要找第 `2～4` 個位置：

```text
P[4] - P[1]
```

也就是：

```text
8 - 2 = 6
```

因此區間 `[l, r]`：

```cpp
sum = prefix[r] - prefix[l - 1];
```

這也是競程中最常見的寫法。

---

# 7. 核心公式

建立 Prefix Sum：

```cpp
prefix[i] = prefix[i - 1] + a[i];
```

查詢區間 `[l, r]`：

```cpp
sum = prefix[r] - prefix[l - 1];
```

也就是：

$$
\boxed{sum(l,r)=P[r]-P[l-1]}
$$

---

# 8. 複雜度

假設：

- 陣列大小為 `N`
- 有 `Q` 次區間查詢

### 暴力

每次查詢最壞：

$$
O(N)
$$

`Q` 次查詢：

$$
O(QN)
$$

### Prefix Sum

先建立 Prefix Sum：

$$
O(N)
$$

每一次區間查詢只需要做一次減法：

$$
O(1)
$$

`Q` 次查詢：

$$
O(Q)
$$

因此總複雜度：

$$
\boxed{O(N+Q)}
$$

---

# 9. 範例程式

### Python

```python
n = int(input())
a = list(map(int, input().split()))

prefix = [0] * (n + 1)

for i in range(1, n + 1):
    prefix[i] = prefix[i - 1] + a[i - 1]

l, r = map(int, input().split())

print(prefix[r] - prefix[l - 1])
```

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> a(n + 1);
    vector<long long> prefix(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        prefix[i] = prefix[i - 1] + a[i];
    }

    int l, r;
    cin >> l >> r;

    cout << prefix[r] - prefix[l - 1] << endl;
}
```

---

# 10. 題目練習

[f174.m6a2-蛋糕(Cake)](https://zerojudge.tw/ShowProblem?problemid=f174)

[g597.3. 生產線](https://zerojudge.tw/ShowProblem?problemid=g597)