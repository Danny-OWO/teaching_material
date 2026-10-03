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
