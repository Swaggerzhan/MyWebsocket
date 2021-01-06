# 头文件介绍
* Websocket.h为解析websocket协议的类所在文件。
    * parseHandshake解析websocket握手包
        ```C++
        WebSocketFrameType parseHandshake(char* input_frame, int input_len)
        ```
        
    * answerHandshake生层回应的websocket握手包
    
        ```C++
        string answerHandshake()
        ```
    
    * makeFrame接收websocket上层数据，通过frame_type指定传输的帧类型，以及msg原始数据，生成对应的websocket包

        ```C++
        int makeFrame(WebSocketFrameType frame_type, unsigned char* msg, int msg_length, unsigned char* buffer, int buffer_len){

        ```
    
    * getFrame解析websocket包，分解客户端发送的数据包，解掩码，并写入out_buffer中，并返回解析的websocket帧类型

        ```C++
        WebSocketFrameType getFrame(unsigned char* in_buffer, int in_length, unsigned char* out_buffer, int out_size, int* out_length){

        ```

* InterFace.h为InterFace类所在文件
    * RUN为整个项目入口
    
        __其调用了私有方法MainLoop启动__
        ```C++
        void RUN();
        void MainLoop();
        ``` 
    * newConnection处理新用户链接

        ```C++
        void newConnection();
        ``` 
    
    * process处理用户请求
    
        ```C++
        void process(int client_fd);
        ```

* UserHandler.h为UserHandler类所在文件
    * sendMsg向目标id发送信息
        
        ```C++
        void sendMsg(UserMap* userMap, int target_id, std::string raw_msg);
        ```
        
    * recvMsg接收信息
        __recvMsg通过RecvCode判断是否发生了客户端关闭事件，通知上层__

        ```C++
        RecvCode recvMsg(UserMap* user, int client_fd);
        ```
        
        
        
* WebsocketHandler.h为websocket层类所在文件
    __WebsocketHandler相对上层透明。__
    * sendMsg发送数据，其内部自动封装成websocket帧并且发送给下层tcpHandler
    
        ```C++
        void sendMsg(int target_fd, std::string msg);
        ```
        
    * recvMsg接收数据，其内部自动解websocket包并传送至上层UserHandler
        __recvMsg会返回RecvCode来判断是否发生了客户端关闭事件，并且通知上层__
        
        ```C++
        RecvCode recvMsg(int client_fd);
        ```
        
* TcpHandler.h为TcpHandler类所在文件

    * sendMsg发送数据到对应客户端上

        ```C++
        void sendMsg(int target_fd, std::string binary_msg);
        ```
    
    * recvMsg接收数据
        __通过RecvCode通知上层客户端是否发生断开链接事件__
        
        ```C++
        RecvCode recvMsg(int client_fd, char* binary_buf, int &msg_buf_len);
        ```
    
    
    注： JsonCrypto引用了jsoncpp进行json数据解析，被UserHandler类调用。其中各个类还包含各自层面的登陆与握手等。