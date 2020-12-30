//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_TCPHANDLER_H
#define MYWEBSOCKET2_TCPHANDLER_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "utility.h"


class TcpHandler{


private:

    int _fd = -1; // not used yet

    char _recv_buf[2048];

public:

    /**
     * send message
     * @param target_fd
     * @param binary_msg
     */
    void sendMsg(int target_fd, std::string binary_msg);

    /**
     * recv message
     * @param client_fd
     * @param binary_buf
     * @return RecvCode Normal to tell upper layer has data
     */
    RecvCode recvMsg(int client_fd, char* binary_buf, int &msg_buf_len);


    void close_fd(int fd);

private:

    /**
     * clear all buff
     */
    void clearBuff();


};


#endif //MYWEBSOCKET2_TCPHANDLER_H
