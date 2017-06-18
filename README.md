## 执行
1. mkdir build && cd build
2. cmake .. && make
3. cd .. && cd bin
4. bin目录下有server，和测试用的client

## 功能
1. 可以添加坐标点
2. 给一个坐标和范围可以查询周围坐标点

## 编译运行
1. 没有内存错误 
2. 线程安全  

## 结构
1. 业务 网络 近邻算法 三个部分分离
2. 考虑到目前业务比较简单，所以采用直白的注入方式
3. 代码目录
- /geo geo算法库
- /dep 依赖 gmock gtest kdtree protobuf
- /include 头文件
- /lib 库
- /src 网络
- /test server client unittest 入口
- /bin 生成文件目录
- /log 存放日志目录

业务分析
1. 添加位置的请求数量要远远多于计算位置
2. 计算是耗时远远多于简单添加位置
3. 连接会比较多，IO负担较大

技术分析
1. EPOLLET EPOLLLT 的选择？选择ET模式
2. oneshot 的选择？多线程中，选择oneshot
3. 传参方式与检查
4. 粘包解决与测试：
5. GeoHash

TODO
1. geohash 