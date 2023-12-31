### 1.0.0

(2022-08-23)

**更新**

- 修复国密SSL使用普通SSL握手的流程的流程
- 修复boostssl可能crash的一些问题

### 1.0.0-rc4

(2022-06-30)

**更新**

- 日志中增加模块名前缀
- SSL握手过程中解析公钥
- `Message`结构变更，提取抽象类，添加`version`字段
- `Handlers`相关函数加锁，保证线程安全
- 增加`setReconnectedPeers`接口，支持更新重连的节点列表
- `ASIO`修改为单线程驱动单个`io_context`模型

### 1.0.0-rc3

(2022-03-31)

**更新**

- 关闭`websocket`压缩功能

**修复**

- 修复网络断链时调用`session`发送消息导致`crash`的问题

### 1.0.0-rc2

(2022-02-22)

**新增**

- 引入`bcos-utilities`依赖，删除`utilities`目录

**修复**

- 修复`stop`操作可能导致`crash`的问题

### 1.0.0-rc1

(2021-12-09)

**简介**

基于`boostssl`和`tassl`实现的c++通用网络库

**功能**

- 基于`websocket`协议，同时支持服务端与客户端模式
- 支持`http`服务端模式
- 支持`ssl`、国密`ssl`连接
- 支持自定义通信协议
