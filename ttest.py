from collections import deque
import time

start_time = time.perf_counter()

# 初始化佇列
q = deque()

# Push：從尾端加入元素
for i in range(100000):
    q.append(i)

# Front & Pop：安全地從前端依序讀取並移除
while q:
    print("最前端元素:", q[0])   # 讀取最前面的元素
    q.popleft()                  # 移除最前面的元素

end_time = time.perf_counter()
execution_time = end_time - start_time
print(f"Execution time: {execution_time:.6f} seconds")