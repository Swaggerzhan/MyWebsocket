//
// Created by swagger on 2020/12/29.
//

#include "../include/TcpHandler.h"


void TcpHandler::sendMsg(int target_fd, std::string binary_msg) {
    write(target_fd, binary_msg.c_str(), binary_msg.length());
}


RecvCode TcpHandler::recvMsg(int client_fd, char *binary_buf, int &msg_buf_len) {
    // clear buff for new request
    //clearBuff();


    int str_len = read(client_fd, binary_buf, BUF_SIZE);
    if ( 0 == str_len){ // close time
        close(client_fd);
        return CloseEvent;
    }
    std::cout << "tcp layer len: " << str_len << std::endl;
    std::cout << "tcp layer: " << binary_buf << std::endl;
    msg_buf_len = str_len;

    return Normal;
}


void TcpHandler::clearBuff() { memset(_recv_buf, 0, BUF_SIZE); }


void TcpHandler::close_fd(int fd){ close(fd); }