# 第 11 章：對應表 `map`

`map` 用「鍵」找到對應的「值」。每個鍵都是唯一的，使用前要引入 `<map>`。

## 1. 建立與存取

```cpp
map<string, string> capitals;
capitals["Japan"] = "Tokyo";
capitals["France"] = "Paris";

cout << capitals["Japan"] << '\n';
```

`map<string, string>` 表示鍵和值都是字串。也可以使用其他型別，例如 `map<string, int>`。

## 2. 檢查鍵是否存在

```cpp
string country;
cin >> country;

if (capitals.count(country) > 0) {
    cout << capitals[country] << '\n';
} else {
    cout << "unknown\n";
}
```

直接讀取不存在的鍵，例如 `capitals[country]`，會自動建立一筆資料。因此只想檢查時，要先使用 `count` 或 `find`。

## 3. 計算出現次數

```cpp
int n;
cin >> n;

map<string, int> frequency;
for (int i = 0; i < n; i++) {
    string word;
    cin >> word;
    frequency[word]++;
}
```

新的鍵會先得到整數初始值 `0`，所以可以直接加一。

## 4. 走訪與刪除

```cpp
for (const auto& entry : frequency) {
    cout << entry.first << ' ' << entry.second << '\n';
}

frequency.erase("apple");
```

`entry.first` 是鍵，`entry.second` 是值。`map` 會依照鍵的順序走訪資料。

## 5. 常用操作整理

| 寫法 | 功能 |
|---|---|
| `data[key]` | 取得或建立鍵對應的值 |
| `data.at(key)` | 取得值，但不建立新資料 |
| `data.count(key)` | 檢查鍵是否存在 |
| `data.find(key)` | 尋找鍵的位置 |
| `data.erase(key)` | 刪除一組資料 |
| `data.size()` | 資料筆數 |
| `data.clear()` | 刪除所有資料 |

若 `key` 不存在，`at(key)` 會丟出 `out_of_range`，因此通常要先用 `count` 或 `find` 檢查。

使用 `find` 可以只搜尋一次：

```cpp
auto it = capitals.find(country);
if (it != capitals.end()) {
    cout << it->second << '\n';
} else {
    cout << "unknown\n";
}
```

`it->first` 是鍵，`it->second` 是值。

## 6. 找出出現最多次的資料

先建立次數表，再找最大值：

```cpp
string bestWord;
int bestCount = 0;

for (const auto& entry : frequency) {
    if (entry.second > bestCount) {
        bestWord = entry.first;
        bestCount = entry.second;
    }
}

cout << bestWord << ' ' << bestCount << '\n';
```

因為 `map` 按照鍵排序，次數相同時，這個寫法會保留字典順序較前面的鍵。

## 7. 值也可以是容器

一個鍵可能對應多個值，例如國家與城市、使用者與權限：

```cpp
map<string, set<string>> cities;
cities["Japan"].insert("Tokyo");
cities["Japan"].insert("Osaka");

for (const string& city : cities["Japan"]) {
    cout << city << '\n';
}
```

選擇資料結構時，先確認題目需要的是單一值、計數，還是一組不重複的值。
