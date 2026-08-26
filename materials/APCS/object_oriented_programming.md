# 物件導向程式設計

## 1. 什麼意思?

我們之前寫程式時，通常會把 **資料** 和 **函式** 分開處理。  
但如果我們想設計遊戲這種，對於各個物件有很多特性的程式時，我們便會傾向把資料和其可以用的函式捆在一起使用： **也就是自己設計自己的資料型態**。

例如「狗」：
```text
資料 / 狀態：
- name
- age
- weight

行為：
- bark()
- eat()
- sleep()
```

這時候如果我們引進了更多動物，我們便不會錯誤地引用，比方說讓 人類 bark (excluding ishowspeed)


## 2. 再舉個例子

痾，你是一名偵探，正在調查銀行偷竊案。


<img src="./resources/KOBE.jpg" width="300">



```text
姓名：小黑
年齡：24
失竊案發生時間在哪：銀行附近
失竊案發生時間在做甚麼：當 KOBE 仰望 凌晨四點 的 台北市
```


<img src="./resources/gede.jpg" width="300">



```text
姓名：基德
年齡：18
失竊案發生時間在哪：銀行附近
失竊案發生時間在做甚麼：疑似在玩飛行器
```

像這樣的資料有無數個，甚至我們也想加入更多具體事項。   

當然，身為專業的偵探，**你不可以有人叫小黑就說是小偷，也不可以因為基德沒有發預告就說不是基德偷的**。   

如果在不借助其他軟體或是檔案格式下，利用python和C++想要把資料讀取並有效的利用資料，我們需要**自己設定資料型態**，否則也只能用也不是說特別好用的字典了。

## 3. 自己設定資料型態 (C++)

在 C++ 裡面，我們可以使用 `class` 來建立自己的資料型態。

```cpp
#include <bits/stdc++.h>
using namespace std;

class Suspect
{
public:
    string name;
    int age;
    string where;
    string what;

    Suspect(string n, int a, string wh, string wt)
    {
        name = n;
        age = a;
        where = wh;
        what = wt;
    }
};

int main()
{
    Suspect sus1("small_black", 24, "near bank", "pretend to be KOBE");
    Suspect sus2("GD", 18, "near_bank", "playing hang glider");

    cout << sus1.name << endl;
    cout << sus2.age << endl;
}
```

```text
small_black
18
```

C++ 使用 **Constructor（建構子**。來達成建立物件的效果：  

```cpp
Suspect(string n, int a, string wh, string wt)
{
    name = n;
    age = a;
    where = wh;
    what = wt;
}
```

Constructor 的名字會和 `class` **完全相同**，而且不需要寫回傳型態。

當我們建立：

```cpp
Suspect sus1("small_black", 24, "near bank", "pretend to be KOBE");
```

`Suspect(...)` 的 Constructor 就會自動被執行，幫我們設定這個物件一開始的資料。

除了設定自己的資料和數值外，我們也能設計出獨屬這個自訂資料型態的函式。這種放在 class 裡面的函式稱為 **Method（方法）**。

```cpp
#include <bits/stdc++.h>
using namespace std;

class Suspect
{
public:
    string name;
    int age;
    string where;
    string what;

    Suspect(string n, int a, string wh, string wt)
    {
        name = n;
        age = a;
        where = wh;
        what = wt;
    }

    void list_identity()
    {
        cout << "name: " << name << endl;
        cout << "age: " << age << endl;
        cout << "where: " << where << endl;
        cout << "what: " << what << endl;
    }
};

int main()
{
    Suspect sus1("small_black", 24, "near bank", "pretend to be KOBE");
    Suspect sus2("GD", 18, "near_bank", "playing hang glider");

    sus1.list_identity();
}
```

```text
name: small_black
age: 24
where: near bank
what: pretend to be KOBE
```

注意這裡的呼叫方式喔，是：

```cpp
sus1.list_identity();
```

而不是：

```cpp
list_identity(sus1);
```

是一樣的。

另外 C++ 多了一個：

```cpp
public:
```

C++ 的 `class` 預設不允許我們直接從外面存取裡面的東西，因此如果希望可以像：

```cpp
sus1.name
sus1.age
sus1.list_identity()
```

這樣直接使用，就需要先把它們放在 `public:` 底下。

像這樣，我們可以把屬於 `Suspect` 的資料與功能全部整理在一起，不需要在外面每次使用四個 `cout` 來達成目的。

## 4. 自己設定資料型態 (Python)

在 python 裡面，我們會使用 class 來進行自己設定資料型態。

```python
class Suspect:
    def __init__(self, name, age, where, what):
        self.name = name
        self.age = age
        self.where = where
        self.what = what

sus1 = Suspect("small_black", 24, "near bank", "pretend to be KOBE")
sus2 = Suspect("GD", 18, "near_bank", "playing hang glider")

print(sus1.name)
print(sus2.age)
```

```text
small_black
18
```

**__init__** 這個函式會是一創建該資料型態的物件時會自動啟動的function，記得要加上 **self**。  

除了設定自己的資料和數值外，我們也能設計出獨屬這個自訂資料型態的函式。

```python
class Suspect:
    def __init__(self, name, age, where, what):
        self.name = name
        self.age = age
        self.where = where
        self.what = what
    def list_identity(self):
        print("name:", self.name)
        print(f"age: {self.age}")
        print("where:", self.where)
        print("what:", self.what)

sus1 = Suspect("small_black", 24, "near bank", "pretend to be KOBE")
sus2 = Suspect("GD", 18, "near_bank", "playing hang glider")

sus1.list_identity()
```

```text
name: small_black
age: 24
where: near bank
what: pretend to be KOBE
```

注意這裡的呼叫方式喔， 是 **sus1.list_identity()** 而不是 **list_identity(sus1)**  
像這樣，我們可以很好維護我們的程式碼，也不用在外面每次用四個print來達成目的。
