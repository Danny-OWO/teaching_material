# 堆疊和佇列

很好，你是跟我一樣從小學習python的小孩。那麼恭喜你，你八成對stack和queue的概念差不多跟你對幼稚園校門口那隻蒼蠅一樣，完全不認識。
這份md會介紹堆疊和佇列，但說真的沒人講中文，所以我們都說**stack and queue**

## 1. STACK是什麼? 

若要給予你 stack 的最佳觀念，你可能需要先下樓，去全聯之類的，幫我買**一罐品克洋芋片**，記得要買圓筒狀的：因為我很挑食。我可能會要你幫我一片片拿出來放到盤子上擺盤：因為我很重視情緒價值，沒有情緒價值的洋芋片我不吃。如果只給你開一個開口，你是不是只能從上面一片一片拿出來。你會發現最先放進桶子的洋芋片反而是最後拿出來的。這樣的行為又稱為**stack** which means **LAST IN FIRST OUT**



## 2. QUEUE是什麼?

若要給予你 queue 的最佳觀念，你可能需要先下樓，去找那種網紅手搖飲名店比如說**爆睡一整天**，然後去排隊幫我買個珍奶之類的。
如果小明跟小華排在你後面，你先結帳，結完帳了應該是你先去側邊等而不是小明或小華吧，這正是排隊。又或是**queue** which means **FIRST IN FIRST OUT**。


## 3. Stack 實作 (C++)

在吃完洋芋片之後，我們要回來寫程式了。但在那之前，**請你先去洗手**，不要把鍵盤搞得油油的。
我們先看原生就有stack的c++該如何使用stack
```cpp
#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30); 

    cout << "Stack size: " << s.size() << "\n"; 

    while (!s.empty()) {
        std::cout << "Top element: " << s.top() << "\n";
        s.pop();
    }

    return 0;
}
```
執行結果：
```text
Stack size: 3
Top element: 30
Top element: 20
Top element: 10
```

裡面運用到：

| 操作 (Operation) | 函數 (Function) | 說明 (Description) | 時間複雜度 (Time Complexity) |
| :--- | :--- | :--- | :--- |
| **Push** | `s.push(val)` | 將元素加入至堆疊頂端。 | O(1) |
| **Pop** | `s.pop()` | 移除頂端元素（**不**會回傳該元素）。 | O(1) |
| **Top** | `s.top()` | 回傳頂端元素的引用（Reference）。 | O(1) |
| **Empty** | `s.empty()` | 若堆疊為空，則回傳 `true`。 | O(1) |
| **Size** | `s.size()` | 回傳堆疊中元素的總數。 | O(1) |

## 4. Stack 實作 (Python)

對你是個學習**蟒蛇**的小孩，所以你沒有看前面的**排列組合加加**，至於為什麼學習python的過程裡面很少會提到stack 以及 queue 的原因多半是因為原生的list太好用了。但要小心，好用的代價就是有可能一不小心掉進了TLE的陷阱。

至於實作Stack的方式有很多，最基本的就是利用list。

```python
stack = []

stack.append(10)
stack.append(20)
stack.append(30)  

print(stack[-1])   

while stack:
    print(stack.pop())  
```


執行結果：

```text
30
30
20
10
```

裡面運用到：
| 操作 (Operation) | 列表語法 (List Method) | 說明 (Description) | 時間複雜度 (Time Complexity) |
| :--- | :--- | :--- | :--- |
| **Push (推入)** | `stack.append(val)` | 將元素加入至堆疊頂端。 | O(1) |
| **Pop (彈出)** | `stack.pop()` | 移除並**回傳**頂端的元素。 | O(1) |
| **Top (查看頂端)** | `stack[-1]` | 讀取頂端元素，但不移除它。 | O(1) |
| **Empty (檢查空值)** | `not stack` | 檢查堆疊是否為空。 | O(1) |
| **Size (取得長度)** | `len(stack)` | 回傳堆疊內元素的總數。 | O(1) |



## 5. Queue 實作 (C++)

吃完洋芋片就是要喝珍奶啦! 無論你剛有沒有買你自己的分，你幫我買的先給我再說。**記得不要把飲料灑到電腦上**。

```cpp
#include <iostream>
#include <queue> 
using namespace std;

int main() {
    queue<int> q;

    q.push(10); // [10]
    q.push(20); // [10, 20]
    q.push(30); // [10, 20, 30]

    cout << "Queue size: " << q.size() << "\n";      // Output: 3
    cout << "Last added element: " << q.back() << "\n"; // Output: 30

    while (!q.empty()) {
        cout << "Front element: " << q.front() << "\n"; 
        q.pop(); 
    }

    return 0;
}
```
輸出結果：
```text
Queue size: 3
Last added element: 30
Front element: 10
Front element: 20
Front element: 30
```

裡面運用到：


| 操作 (Operation) | 佇列語法 (Queue Method) | 說明 (Description) | 時間複雜度 (Time Complexity) |
| :--- | :--- | :--- | :--- |
| **Push (推入)** | `q.push(val)` | 將元素加入至佇列尾端。 | O(1) |
| **Pop (彈出)** | `q.pop()` | 移除最前端的元素。 | O(1) |
| **Front (查看前端)** | `q.front()` | 讀取最前端元素，不移除它。 | O(1) |
| **Back (查看尾端)** | `q.back()` | 讀取最後端元素，不移除它。 | O(1) |
| **Empty (檢查空值)** | `q.empty()` | 檢查佇列是否為空。 | O(1) |
| **Size (取得長度)** | `q.size()` | 回傳佇列內元素的總數。 | O(1) |

## 6. Queue 實作 (Python)

想要實作queue，我們必須讓先進去的元素優先取出。如果你想實作stack一樣利用好方便好方便的list，就會掉進 **TLE的陷阱**。
還記得嗎，剛剛stack時，我們使用list裡面的pop()，將最尾端的項目取出，而這樣的時間複雜度是 **O(1)**。而在queue裡面，我們必須將最前端的元素取出，也就是pop(0)，而在python裡面，電腦會將後面所有元素往前搬一格，所以時間複雜度是 **O(n)**

也就是說我們不能利用list去模擬queue了，於是有人設計了 **deque**

```python
from collections import deque

q = deque()

q.append(10)
q.append(20)
q.append(30)

print("佇列大小:", len(q))       
print("最後端元素:", q[-1])    

while q:
    print("最前端元素:", q[0])   
    q.popleft()                  
```

執行結果：

```text
佇列大小: 3
最後端元素: 30
最前端元素: 10
最前端元素: 20
最前端元素: 30
```

裡面運用到：
| 操作 (Operation) | 佇列語法 (Deque Method) | 說明 (Description) | 時間複雜度 (Time Complexity) |
| :--- | :--- | :--- | :--- |
| **Push (推入)** | `q.append(val)` | 將元素加入至佇列尾端。 | O(1) |
| **Pop (彈出)** | `q.popleft()` | 移除並**回傳**最前端的元素。 | O(1) |
| **Front (查看前端)** | `q[0]` | 讀取最前端元素，但不移除它。 | O(1) |
| **Back (查看尾端)** | `q[-1]` | 讀取最後端元素，但不移除它。 | O(1) |
| **Empty (檢查空值)** | `not q` | 檢查佇列是否為空。 | O(1) |
| **Size (取得長度)** | `len(q)` | 回傳佇列內元素的總數。 | O(1) |



## 6. 如果你不信邪

* 利用 **deque** 去進行100000筆資料的輸入和取出： Execution time: **7.062281** seconds
* 利用 **list**  去進行100000筆資料的輸入和取出：Execution time: **14.833821** seconds

**沒錯差了一倍**

## 7. stack and queue 練習題目
