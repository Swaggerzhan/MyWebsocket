# MyWebsocket聊天服务器(test)
### websocket连接后发送登陆包(以下包都以json格式发送)
    {
        "id": "user's id",      ------>ValueType = Int
        "name": "user's name"   ------>ValueType = String
    }
### websocket登陆失败或者登陆成功收到的
    {"type": -1, "message": "handshake failed!"} //失败
    {"type": 3, "message": "handshake success"} //成功
### 向已经登陆的websocket fd发送数据
     {
        "source_id": "发送者ID",       ----->ValueType = Int
        "des_id": "接收者ID",        ----->ValueType = Int
        "message": "message body",     ----->ValueType = String
        "type": 11                     ----->ValueType = Int
    }
### 收到的聊天数据包
    {
        "source_id": "发送者ID ",       ------>ValueType = Int
        "source_name": "发送者名字",     ------>ValueType = String
        "des_id": "接收者ID",          ------>ValueType = Int
        "message": "message body",    ------>ValueType = String
        "time": 1605578865,         ------>ValueType = Int
        "type": 1,                   ------>ValueType = Int 
    }
    时间time字段需要自己在JsonCrypto.cpp中自行定义
## 文件结构
|--include/头文件
|
|-src/源代码
|
|-main.cpp
|
|-makefile
|
|-server
* InterFace.h 主服务器及其入口文件
* JsonCrypto.h json解释方法类
* TcpHandler.h tcp层
* WebsocketHandler.h websocket层
* Websocket.h websocket协议解包类
* base64.h和 sha1.h为公有库
* utility.h 公共头文件
* UserMap.h 维护用户的表
* 项目依赖jsoncpp库

##### 注
本例子是建立在epoll上的，并且项目依赖jsoncpp库
其中有一些debug用的打印用例。
