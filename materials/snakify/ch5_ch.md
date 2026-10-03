# 第 5 章：字串

`string` 用來儲存一串文字。使用前要引入 `<string>`。

## 1. 讀取字串

```cpp
string word;
cin >> word;          // 讀到空白為止
```

要讀取包含空白的整行文字，可以使用：

```cpp
string line;
getline(cin, line);
```

若前面剛使用過 `cin >>`，可以寫成 `getline(cin >> ws, line);`，先略過留下的空白與換行。

## 2. 長度與索引

字元的位置從 `0` 開始。

```cpp
string s = "Hello";
cout << s.size() << '\n';  // 5
cout << s[0] << '\n';      // H
cout << s[s.size() - 1];    // o
```

索引必須在有效範圍內。單一字元使用 `char` 儲存。

```cpp
char first = s[0];
s[0] = 'h';
```

## 3. 連接與子字串

```cpp
string first = "good";
string second = "day";
string message = first + " " + second;

string s = "abcdef";
cout << s.substr(2, 3);  // cde
```

`substr(起點, 長度)` 會取出一段新字串。

## 4. 尋找文字

```cpp
string s = "abracadabra";
size_t pos = s.find("cad");

if (pos != string::npos) {
    cout << pos << '\n';
}
```

找不到時，`find` 會回傳 `string::npos`。

字串也能使用迴圈逐字處理：

```cpp
for (char c : s) {
    cout << c << '\n';
}
```

## 5. 常用字串操作

| 寫法 | 功能 |
|---|---|
| `s.empty()` | 檢查字串是否為空 |
| `s.front()` | 第一個字元 |
| `s.back()` | 最後一個字元 |
| `s += text` | 在尾端接上文字 |
| `s.insert(pos, text)` | 在 `pos` 插入文字 |
| `s.erase(pos, length)` | 從 `pos` 刪除指定長度 |
| `s.replace(pos, length, text)` | 將一段文字換掉 |
| `s.find(text)` | 尋找第一次出現的位置 |
| `s.rfind(text)` | 尋找最後一次出現的位置 |

```cpp
string s = "I like cats";
s.replace(7, 4, "dogs");  // I like dogs
s.erase(1, 1);             // Ilike dogs
s.insert(1, " ");         // I like dogs
```

這些函式的 `length` 是「字元數量」，不是結束位置。

## 6. 反轉與計數

引入 `<algorithm>` 後，可以使用 `reverse` 與 `count`：

```cpp
#include <algorithm>

string s = "banana";
int numberOfA = count(s.begin(), s.end(), 'a');

reverse(s.begin(), s.end());
cout << s << '\n';  // ananab
```

只反轉一部分時，結束位置不包含在範圍內：

```cpp
reverse(s.begin() + left, s.begin() + right);
```

這會反轉索引 `[left, right)`。

## 7. 逐字修改

需要修改原字串時，使用參考 `char&`：

```cpp
for (char& c : s) {
    if (c == 'a') {
        c = 'A';
    }
}
```

若要刪除每隔固定位置的字元，建立一個新字串通常最簡單：

```cpp
string result;
for (int i = 0; i < s.size(); i++) {
    if ((i + 1) % 3 != 0) {
        result += s[i];
    }
}
```
