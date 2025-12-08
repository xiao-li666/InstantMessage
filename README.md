### 即时通讯项目介绍

这是一个即时通讯项目，客户端使用Qt实现界面交互，用QListWidget实现好友列表，采用Qt network模块封装http和tcp服务，实现添加好友，好友通信功能。

服务端使用分布式设计，包括GateServer,StatusServer,VerifyServer和两个ChatServer。各服务之间通过grpc通信，GateServer对外提供http服务，主要实现注册登录等请求，StatusServer主要用于实现各通信服务器的负载均衡。ChatServer采用asio网络库实现tcp可靠长连接异步通信与转发，采用多线程模式封装io_context提升并发性能，数据库采用mysql并通过MysqlConnector封装连接池，封装redis连接池提供缓存服务，同时分装grpc连接池实现多服务并发访问

**所使用技术**：多线程，网络编程，Qt信号槽，ASIO网络库，GRPC框架，mysql，redis，设计模式

项目整体框架如下：
<img width="1071" height="661" alt="model" src="https://github.com/user-attachments/assets/5e5a051d-5254-4760-8e62-0d527d50d874" />

![图片](E:\cppCode\MyProject\images\model.png)

*项目功能概述：*

**注册请求**：客户端与GateServer进行Http连接，当用户登录注册操作中获取验证码时向GateServer发送./getVerifyCode的请求，GateServer作为VerifyGrpcClient请求VerifyServer验证服务器向注册邮箱发送验证码同时VerifyServer将验证码保存在redis中并设置过期时间，客户端发送注册请到GateServer，GateServer首先匹配redis中的验证码判断是否正确，正确之后查看mysql中该用户是否存在，如果不存在将注册信息保存在mysql中并告知客户端注册成功，否则返回相应错误码

**登录请求**：客户端发送./login的请求给GateServer，GateServer从mysql中查询用户信息以及验证密码是否正确，没查到信息表示用户不存在，如果查询到信息以及密码正确，GateServer作为StatusGrpcClient执行GetChatServer来获取建立tcp连接数量最少的ChatServer的ip和port以及StatusServer中为登录用户生成的token，客户端收到ip,port,token后根据ip和port与要登录的ChatServer建立连接，在ChatServer中处理登录请求时现在校验token是否和用户匹配，匹配后在redis中查询用户信息，如果查询不到则在mysql中查询用户信息并保存在redis中，然后更新redis中保存的相应ChatServer的登录数量，并且将该用户的uid和ChatServer的Name保存在redis中

**认证以及收发消息**：ChatServer收到客户端发送的认证请求或者发送消息任务时，首先查看对方所在服务器，判断如果在同一个服务器上则直接进行消息转发以及相应的逻辑操作，如果不在同一个服务器则该ChatServer作为grpc客户端向对方所在服务器发送请求，在grpc服务端实现消息转发以及相应的逻辑操作

*具体模块介绍：*

**GateServer**:网关服务器，主要处理用户的登录，注册请求，与VerifyServer通过grpc实现通信主要实现验证服务，同时与StatusServer也通过grpc实现通信主要实现登录时负载均衡的功能

**VerifyServer**：向注册用户发送验证码

**StatusServer**：状态服务器，主要用于实现负载均衡，为登录用户选择在线用户数量最少的服务器用户登录

**ChatServer**：聊天服务器，主要用与实现用户之间通信的任务
