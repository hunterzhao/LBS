业务分析
1. 添加位置的请求数量要远远多于计算位置
2. 计算是耗时远远多于简单添加位置
3. 连接会比较多，IO较大
4. 业务层如何与网络层分割

技术分析
1. TCP不需要维持长连接
2. EPOLLET EPOLLLT 的选择？
3. oneshot 的选择？多线程中，选择oneshot
4. 传参方式与检查
bug:
1. epoll 线程安全么？