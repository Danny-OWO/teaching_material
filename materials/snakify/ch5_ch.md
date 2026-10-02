# 第 5 章：字串

字串（string）是一串依序排列的字元。本章會介紹字串的輸入、索引、子字串與搜尋，並特別指出 C++ 和 Python 在這些操作上的差異。

## 1. 字串

C++ 使用 `string` 儲存字串，使用前要引入 `<string>`。

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string first_name;
    cin >> first_name;          // 讀到空白為止

    string full_name;
    getline(cin >> ws, full_name); // 讀取一整行，包含空白

    cout << first_name << '\n';
    cout << full_name << '\n';
}
```

字串常值可以放在雙引號中。兩個字串可以用 `+` 串接：

```cpp
string hello = "Hello";
string name = "Harry";
string message = hello + ", " + name + "!";
cout << message << '\n'; // Hello, Harry!
```

單引號表示一個 `char`，雙引號才表示字串：`'A'` 是字元，`"A"` 是字串。兩者不是同一種型別。

C++ 沒有 Python 的字串重複運算，例如 `"ha" * 3`。可以改用迴圈：

```cpp
string result;
for (int i = 0; i < 3; i++) {
    result += "ha";
}
cout << result << '\n'; // hahaha
```

使用 `size()` 或 `length()` 可以取得字串儲存的元素數量，兩者效果相同：

```cpp
string s = "Hello";
cout << s.size() << '\n';   // 5
cout << s.length() << '\n'; // 5
```

對本章使用的英文字串而言，一個元素就是一個字元；但在常見的 UTF-8 編碼下，一個中文字通常占多個位元組。因此 `string("台大").size()` 不一定是 `2`。`std::string` 很擅長存放位元組，卻不懂人類眼中的 Unicode 字元；需要處理中文切割時，不能直接照搬本章的索引方法。

`size()` 回傳的是無號整數型別 `size_t`。如果只是走訪字串，可以直接使用範圍式 `for` 迴圈，避開有號與無號整數比較的問題：

```cpp
for (char c : s) {
    cout << c << '\n';
}
```

數字轉成字串可使用 `to_string()`：

```cpp
int age = 18;
string text = "I am " + to_string(age) + " years old.";
```

反過來，常見的字串轉數字函式有 `stoi()`、`stoll()` 和 `stod()`，分別轉成 `int`、`long long` 與 `double`。

## 2. 取得單一字元

`s[i]` 會取得索引 `i` 的字元，索引從 `0` 開始：

| 字串內容 | `H` | `e` | `l` | `l` | `o` |
|---|---:|---:|---:|---:|---:|
| 索引 | `s[0]` | `s[1]` | `s[2]` | `s[3]` | `s[4]` |

```cpp
string s = "Hello";
cout << s[0] << '\n';          // H
cout << s[s.size() - 1] << '\n'; // o
```

C++ 不支援 Python 的負索引，因此不能寫 `s[-1]`。這不會取得最後一個字元，反而會造成未定義行為。

`s[i]` 不會自動檢查範圍；若希望索引錯誤時得到明確例外，可以使用 `s.at(i)`。索引超出範圍時，`at()` 會丟出 `out_of_range`。

```cpp
cout << s.at(1) << '\n'; // e
```

字串為空時，`s.size() - 1` 也不是合法索引。若要存取首尾字元，應先確認 `!s.empty()`，再使用 `s.front()` 與 `s.back()`。

## 3. 取得子字串

C++ 沒有 Python 的 `s[a:b]` 切片語法，而是使用：

```cpp
s.substr(起始索引, 字元數量)
```

第二個參數是「長度」，不是結束索引。這是最常寫錯的地方。

```cpp
string s = "Hello";
cout << s.substr(1, 3) << '\n'; // ell
cout << s.substr(1) << '\n';    // ello：從索引 1 取到結尾
cout << s.substr(0, 4) << '\n'; // Hell：去掉最後一個字元
```

若要求的長度超過剩餘字元，`substr()` 只會取到字串結尾：

```cpp
cout << s.substr(1, 100) << '\n'; // ello
```

但是起始索引若大於 `s.size()`，會丟出 `out_of_range`。`s.substr(s.size())` 合法，結果是空字串；再多一格就不合法。

## 4. 字串可以被修改

Python 字串不可變，但 C++ 的 `string` 可以直接修改。不要把 Python 的規則硬套過來。

```cpp
string s = "Hello";
s[0] = 'Y';
s += "!";
cout << s << '\n'; // Yello!
```

將一個字串指定給另一個字串時，會複製內容；之後修改其中一個，不會影響另一個：

```cpp
string a = "Hello";
string b = a;
b[0] = 'Y';

cout << a << '\n'; // Hello
cout << b << '\n'; // Yello
```

## 5. 每隔數個字元取值與反轉

C++ 沒有 Python 的 `s[a:b:d]`。若要每隔固定步數取一個字元，可以使用迴圈：

```cpp
string s = "abcdefgh";
string every_second;

for (size_t i = 0; i < s.size(); i += 2) {
    every_second += s[i];
}

cout << every_second << '\n'; // aceg
```

反轉字串可以引入 `<algorithm>`，再使用 `reverse()`：

```cpp
#include <algorithm>

string s = "Hello";
reverse(s.begin(), s.end());
cout << s << '\n'; // olleH
```

`reverse()` 會直接修改原字串。若仍要保留原內容，先複製一份再反轉。

## 6. 搜尋：`find()` 與 `rfind()`

`find()` 尋找子字串第一次出現的位置，`rfind()` 尋找最後一次出現的位置：

```cpp
string s = "abracadabra";
cout << s.find("abra") << '\n';  // 0
cout << s.rfind("abra") << '\n'; // 7
```

找不到時，回傳的不是 `-1`，而是特殊值 `string::npos`。因此應這樣判斷：

```cpp
size_t position = s.find("cat");

if (position == string::npos) {
    cout << "not found\n";
} else {
    cout << position << '\n';
}
```

`find()` 的第二個參數指定從哪個索引開始搜尋，回傳值仍是相對於完整字串的索引：

```cpp
string s = "one two one";
cout << s.find("one", 1) << '\n'; // 8
```

C++ 的 `find()` 沒有 Python 那種直接指定搜尋右界的第三個參數。需要限制範圍時，可以先取出子字串，或額外檢查找到的位置是否落在範圍內。

## 7. 取代：`replace()`

C++ 的 `replace()` 和 Python 的同名方法意義不同。它接受起始索引與要移除的字元數，再放入新字串：

```cpp
string s = "I like Python";
s.replace(7, 6, "C++");
cout << s << '\n'; // I like C++
```

它不會自動取代所有相符的子字串。若要全部取代，可以搭配 `find()` 重複處理：

```cpp
string s = "one fish, two fish";
string old_text = "fish";
string new_text = "cat";

size_t position = 0;
while (!old_text.empty() &&
       (position = s.find(old_text, position)) != string::npos) {
    s.replace(position, old_text.size(), new_text);
    position += new_text.size();
}

cout << s << '\n'; // one cat, two cat
```

更新 `position` 很重要，否則新字串裡若也包含舊字串，迴圈可能永遠停不下來。

## 8. 計算子字串出現次數

C++ 的 `string` 沒有 `count()` 方法。可以反覆使用 `find()` 計算不重疊的出現次數：

```cpp
string s = "aaaa";
string target = "aa";
int count = 0;
size_t position = 0;

while (!target.empty() &&
       (position = s.find(target, position)) != string::npos) {
    count++;
    position += target.size();
}

cout << count << '\n'; // 2
```

這段程式每次找到後跳過整個 `target`，所以只計算不重疊的出現。若改成 `position++`，同一批字元便可能被重複計算；例如 `"aaaa"` 中可找到三個彼此重疊的 `"aa"`。

> 字串題真正的難點通常不是語法，而是邊界：空字串、找不到、第一個位置、最後一個位置，以及重疊是否應計算。先把這五件事說清楚，程式才不會靠運氣答對。
