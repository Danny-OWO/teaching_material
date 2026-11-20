# APCS 題目整理

這裡整合各級題目與中級練習路線，以 ZeroJudge 歷屆題為主、CSES 補基本功。準備中級可直接從下方「中級：核心練習」開始，依序練習陣列、字串與流程模擬。

分組、順序與「核心／延伸」定位是教學建議；舊制題目不一律等同於新制中級。題目連結通往評測平台，「本站教材」連到現有題解；有程式並不表示已通過完整驗證。

整理日期：2026-11-20。

## 🟢 初級 / 初級題型

1. [**r937. 分糖果**](https://zerojudge.tw/ShowProblem?problemid=r937)

2. [**r938. 學習計劃**](https://zerojudge.tw/ShowProblem?problemid=r938)

3. [**r939. 猜拳**](https://zerojudge.tw/ShowProblem?problemid=r939)

4. [**b964. 成績指標**](https://zerojudge.tw/ShowProblem?problemid=b964)

## 🔵 中級：核心練習

準備中級，先把陣列、字串與流程模擬寫穩。先練會依規則更新狀態，再追求更進階的演算法。以下 12 題建議依序完成。


| 順序 | 題目 | 練習重點 | 自我檢查 | 本站教材 |
|---|---|---|---|---|
| 1 | [CSES Repetitions](https://cses.fi/problemset/task/1069/) | 字串掃描、連續段計數 | 單一字元、全部相同、每個字元都不同；狀態是否初始化？ | [題解與程式](../CSES_problem_set/Introductory_Problems/repetitions/index.md) |
| 2 | [ZeroJudge c295 最大和](https://zerojudge.tw/ShowProblem?problemid=c295) | 每列取最大值、保存結果、依總和篩選 | 輸出是否保留原群組順序？沒有符合者時怎麼輸出？ | 待補 |
| 3 | [ZeroJudge r490 商品包裝地](https://zerojudge.tw/ShowProblem?problemid=r490) | 字串索引、檢查碼、頻率陣列 | 產地 `007` 是否仍輸出三位？是否只統計合法條碼？ | [題解與程式](../ZeroJudge/r490/index.md) |
| 4 | [ZeroJudge q182 字串操作](https://zerojudge.tw/ShowProblem?problemid=q182) | 相鄰交換、兩兩排序、前後半交錯 | 重排是否誤用已覆寫的字元？多次操作是否依序作用？ | 待補 |
| 5 | [ZeroJudge j606 造字程式](https://zerojudge.tw/ShowProblem?problemid=j606) | 索引映射、字元搬移、二維輸出 | 是「第 i 個搬到指定位置」，還是「從指定位置取第 i 個」？ | [題解與程式](../ZeroJudge/j606/index.md) |
| 6 | [ZeroJudge m932 蜜蜂觀察](https://zerojudge.tw/ShowProblem?problemid=m932) | 方向陣列、座標、越界處理 | 候選位置不合法時，原位置與輸出如何處理？ | [題解與程式](../ZeroJudge/m932/index.md) |
| 7 | [ZeroJudge k732 特殊位置](https://zerojudge.tw/ShowProblem?problemid=k732) | 二維陣列、曼哈頓距離、範圍加總 | 距離是否包含等號與中心點？四邊、四角是否正確？ | 待補 |
| 8 | [ZeroJudge b965 矩陣轉換](https://zerojudge.tw/ShowProblem?problemid=b965) | 旋轉、翻轉、逆操作 | 先測非正方形；還原時是否反轉操作順序並使用逆操作？ | [題解與程式](../ZeroJudge/b965/index.md) |
| 9 | [ZeroJudge q837 轉盤得分](https://zerojudge.tw/ShowProblem?problemid=q837) | 環狀索引、字元頻率、多輪模擬 | 正負位移與整圈位移是否正確？下一輪是否保留累積位置？ | [題解與程式](../ZeroJudge/q837/index.md) |
| 10 | [ZeroJudge o712 蒐集寶石](https://zerojudge.tw/ShowProblem?problemid=o712) | 位置、方向、分數與格子狀態 | 分數增加與寶石減少的量不同；遇到障礙是否持續轉向？ | 待補 |
| 11 | [ZeroJudge r488 彗星撞擊](https://zerojudge.tw/ShowProblem?problemid=r488) | 區域掃描、條件式狀態更新 | 先判斷整個影響區域是否擊中恐龍，再決定地形是否改變 | [題解與程式](../ZeroJudge/r488/index.md) |
| 12 | [ZeroJudge r489 航空拍照圖](https://zerojudge.tw/ShowProblem?problemid=r489) | 旋轉座標、逐格比對、百分比 | 非正方形有哪些合法旋轉？整數百分比如何計算？ | [題解與程式](../ZeroJudge/r489/index.md) |

### 模擬題的三個關鍵觀念

- **新舊狀態分開**：q182、j606、b965 可先用新字串或新矩陣保存結果，避免一邊讀一邊覆寫。
- **候選位置與目前位置分開**：m932、o712 先計算下一格，確認合法才移動；移動模擬不需要一開始就套 DFS。
- **先判斷，再更新**：r488 的區域條件會決定後續更新方式，不能看到一格就任意修改所有狀態。

k732 可以先從直接枚舉附近座標開始，依題目限制估算工作量，不必先學二維前綴和。

### CSES 補強與延伸

核心清單中的 Repetitions 優先完成。以下依需要加入，不必為了中級把整個 Sorting and Searching 章節刷完。

| 題目 | 建議定位 | 學習重點 | 本站教材 |
|---|---|---|---|
| [Increasing Array](https://cses.fi/problemset/task/1094/) | 基礎補強 | 線性掃描、維護合法前值、累加修改量；注意答案整數範圍 | [題解與程式](../CSES_problem_set/Introductory_Problems/increasing_array/index.md) |
| [Palindrome Reorder](https://cses.fi/problemset/task/1755/) | 字串補強 | 字元頻率、奇偶判斷、依條件建構回文 | [題解與程式](../CSES_problem_set/Introductory_Problems/palindrome_reorder/index.md) |
| [Distinct Numbers](https://cses.fi/problemset/task/1621/) | 學過排序後補充 | 排序後掃描與去重；分清楚數值範圍和可用的計數方法 | [題解與程式](../CSES_problem_set/Sorting_and_Searching/distinct_numbers/index.md) |
| [Collecting Numbers](https://cses.fi/problemset/task/2216/) | 後段挑戰 | 建立位置陣列，從相鄰數值的位置關係計算輪數 | [題解與程式](../CSES_problem_set/Sorting_and_Searching/collecting_numbers/index.md) |
| [Static Range Sum Queries](https://cses.fi/problemset/task/1646/) | 前綴和延伸 | 預處理區間總和；注意左右端點、索引與整數範圍 | [一維前綴和教材](1d_prefix_sum.md) |

Traffic Lights、Collecting Numbers II、Towers、Grid Path Description、Chessboard and Queens 可留待後續資料結構、搜尋與回溯階段。CSES 的 Introductory Problems 是章節名稱，不代表每題都是入門難度。

## 🟠 中高級 / 中高級題型

1. [**s179. 比例分割**](https://zerojudge.tw/ShowProblem?problemid=s179)

2. [**s180. 觀光旅遊**](https://zerojudge.tw/ShowProblem?problemid=s180)

3. [**s181. 校運代表隊**](https://zerojudge.tw/ShowProblem?problemid=s181)

## 🔴 高級 / 高級題型

1. [**s223. 步道規劃**](https://zerojudge.tw/ShowProblem?problemid=s223)

2. [**s224. 骨牌堆疊**](https://zerojudge.tw/ShowProblem?problemid=s224)

3. [**s225. 貨物運送**](https://zerojudge.tw/ShowProblem?problemid=s225)

4. [**r626. 字母配對**](https://zerojudge.tw/ShowProblem?problemid=r626)

5. [**r627. 列印工廠**](https://zerojudge.tw/ShowProblem?problemid=r627)

6. [**r628. 翻來覆去**](https://zerojudge.tw/ShowProblem?problemid=r628)

## 練習方法與完成判準

每題先寫下「儲存哪些狀態、每一步讀什麼、何時更新、何時結束」，再開始寫程式。

1. 不看解答，先做出能依規則運作的版本。
2. 手算最小輸入、邊界位置、重複資料、連續多次操作，核對中間狀態。
3. 提交評測並修正錯誤；記下失敗原因，包含輸出格式、索引與初始化。
4. 隔幾天重新獨立實作，並解釋時間與空間成本。

**模擬練習**：r488、r489、r490 是 2025 年 10 月同一場新制中級題目，可留作一組。若已看過程式，隔一段時間再重新獨立完成；不要把記得解答當成能在考場解題。

## 來源與延伸閱讀

- [APCS 官方中級題本範例](https://apcs.csie.ntnu.edu.tw/wp-content/uploads/2025/08/02_APCS-%E7%A8%8B%E5%BC%8F%E5%AF%A6%E4%BD%9C%E4%B8%AD%E7%B4%9A%E9%A1%8C%E6%9C%AC%E7%AF%84%E4%BE%8B.pdf)：包含特殊位置、字串解碼、蒐集寶石；實作內容以官方題本為準。
- [ZeroJudge 歷屆題庫](https://zerojudge.tw/Problems?page=2&tag=10%E6%9C%88)：可核對 r488～r490 的場次與題本標示；各題規則與限制見上表題目連結。
- [CSES Problem Set](https://cses.fi/problemset/)：依主題選題，搭配 [本站方法整理](../CSES_problem_set/algorithms.md)。
- [APCS 考試內容](APCS考試內容.md)。
