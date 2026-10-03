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
