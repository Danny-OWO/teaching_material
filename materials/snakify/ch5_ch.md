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

`std::string` 會自己記錄長度，平常不需要手動在結尾加入 `\0`。`\0` 主要會在之後接觸 C-style string 時用到。

## 3. 使用迴圈走訪

需要索引時，使用一般的 `for`：

```cpp
for (int i = 0; i < s.size(); i++) {
    cout << i << ' ' << s[i] << '\n';
}
```

只需要每個字元時，可以使用範圍式迴圈：

```cpp
for (char c : s) {
    cout << c << '\n';
}
```

修改字元時可以透過索引：

```cpp
for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'a') {
        s[i] = 'A';
    }
}
```

## 4. 連接與子字串

```cpp
string first = "good";
string second = "day";
string message = first + " " + second;

string s = "abcdef";
cout << s.substr(2, 3);  // cde
```

`substr(起點, 長度)` 會取出一個新字串。第二個參數是「長度」，不是結束位置。

## 5. 尋找、計數與反轉

`find` 找不到內容時，會回傳 `string::npos`：

```cpp
string s = "abracadabra";
auto pos = s.find("cad");

if (pos != string::npos) {
    cout << pos << '\n';
}
```

引入 `<algorithm>` 後，可以使用 `count` 與 `reverse`：

```cpp
#include <algorithm>

string s = "banana";
int numberOfA = count(s.begin(), s.end(), 'a');

reverse(s.begin(), s.end());
cout << s << '\n';  // ananab
```

常用的基本操作還有：

| 寫法 | 功能 |
|---|---|
| `s.empty()` | 檢查字串是否為空 |
| `s.front()` | 第一個字元 |
| `s.back()` | 最後一個字元 |
| `s += text` | 在尾端接上文字 |
