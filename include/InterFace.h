//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_INTERFACE_H
#define MYWEBSOCKET2_INTERFACE_H

#include <sys/epoll.h>
#include <iostream>
#include "UserHandler.h"
#include "UserMap.h"

class InterFace{

private:

    int _epfd; // epoll fd

    int _demo_sock; // server listen sock

    struct sockaddr_in _local_addr;

    struct epoll_event* _epoll_array; // epoll array

    UserMap* _users; // user map


public:

    InterFace(UserMap* users, int port = 8888);

    void RUN();

private:

    /**
     *  main loop
     **/
    void MainLoop();

    /**
     *  handle new connection
     *
     *  just add new fd to epoll not do anything
     *
     */
    void newConnection();

    /**
     *  handle already connected fd
     *
     **/
    void process(int client_fd);


};


#endif //MYWEBSOCKET2_INTERFACE_H
