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
5. 粘包发生的原因
6. GeoHash


bug:
1. epoll 线程安全么？
2. epoll_Wait后，得到的fd是Bad file descriptor,原因，epoll_add时要考虑顺序
3. 一些固定的接口必须通过原生指针传递资源，但是我想用智能指针管理这些资源，应该怎么做比较优雅呢
4. 文件描述符的关闭时机 myEvent的释放时机, server终止，部分myEvent内存泄漏