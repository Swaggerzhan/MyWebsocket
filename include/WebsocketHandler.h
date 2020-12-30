//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_WEBSOCKETHANDLER_H
#define MYWEBSOCKET2_WEBSOCKETHANDLER_H



#include <iostream>
#include <cstring>
#include "Websocket.h"
#include "TcpHandler.h"

class WebsocketHandler{

private:

    int _fd;

    bool _isHandshake = false;

    char _msg_buf[BUF_SIZE]; // websocket frame

    WebSocket _websocketCrypto;

    TcpHandler tcpHandler;

    char _msg_buf_decode[BUF_SIZE]; // websocket frame decode already!  json data

public:

    WebsocketHandler(int fd);

    /**
     *  send message
     **/
    void sendMsg(int target_fd, std::string msg);

    /**
     *  get _isHandshake
     * @return bool
     */
    bool isHandshake();

    /**
     * set _isHandshake
     */
    void setHandshaked();

    /**
     * recv message
     * @param client_fd
     * @return
     */
    RecvCode recvMsg(int client_fd);

    /**
     * get _msg_buf_decode pointer --> deocde already. json data
     * @return
     */
    char* websocket_frame_to_json_pointer();

    /**
     *  get _msg_buf pointer --->  not decode yet
     **/
    char *websocket_buf_pointer();

    /**
     * clear buff
     */
    void clearBuff();

};

#endif //MYWEBSOCKET2_WEBSOCKETHANDLER_H
