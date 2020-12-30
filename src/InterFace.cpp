//
// Created by swagger on 2020/12/29.
//


#include "../include/InterFace.h"

void InterFace::RUN() {
    MainLoop();
}

InterFace::InterFace(UserMap *users, int port) {
    _users = users;

    _demo_sock = socket(AF_INET, SOCK_STREAM, 0);
    _local_addr.sin_addr.s_addr = INADDR_ANY;
    _local_addr.sin_family = AF_INET;
    _local_addr.sin_port = htons(port);


    bool bDontLinger = false;
    setsockopt(_demo_sock, SOL_SOCKET, SO_REUSEADDR,(const char*)&bDontLinger,sizeof(bool));

    // init sock
    if ( ::bind(_demo_sock, (struct sockaddr*)&_local_addr, sizeof(_local_addr)) < 0){
        perror("bind() error!");
        exit(1);
    }

    if ( ::listen(_demo_sock, LISTEN_SIZE) < 0){
        perror("listen() error!");
        exit(2);
    }

    // init epoll

    // malloc size
    _epoll_array = new struct epoll_event[OPEN_MAX];

    _epfd = epoll_create(OPEN_MAX);
    struct epoll_event events;
    events.data.fd = _demo_sock;
    events.events = EPOLLIN;
    epoll_ctl(_epfd, EPOLL_CTL_ADD, _demo_sock, &events);
}


void InterFace::MainLoop() {
    while (true){
        int res_cl_sz = epoll_wait(_epfd, _epoll_array, OPEN_MAX, -1);
        for (int i=0; i<res_cl_sz; i++){
            if (_epoll_array[i].data.fd == _demo_sock){ // new connection

                newConnection();

            }else{ // data events;

                process(_epoll_array[i].data.fd);
            }
        }
    }
}


void InterFace::newConnection() {
    struct sockaddr_in remote_addr;
    socklen_t remote_addr_sz = sizeof(remote_addr);
    int client_fd = accept(
            _demo_sock,
            (struct sockaddr*)&remote_addr,
            &remote_addr_sz
    );
    if (client_fd < 0){
        perror("accept() error!");
        return;
    }
    // register to epoll
    struct epoll_event events;
    events.data.fd = client_fd;
    events.events = EPOLLIN;
    epoll_ctl(_epfd, EPOLL_CTL_ADD, client_fd, &events);

    // todo upper layer
    // false or true
    bool flag = _users->add(client_fd);
}


void InterFace::process(int client_fd) {
    UserHandler* handler = _users->findByFD(client_fd);
    if (handler == nullptr){
        // wrong, but not happen
        std::cout << "error when find UserHandler*" << std::endl;
        return;
    }
    RecvCode code = handler->recvMsg(_users, client_fd);
    if ( code == CloseEvent){
        // sign from User layer mean close event;
        // delete from epoll
        epoll_ctl(_epfd, EPOLL_CTL_DEL, client_fd, nullptr);
        // delete from userMap
        _users->del(client_fd);
        return;
    }
    // bottom layer doing handshake event
    if ( code == NotHandshake)
        return;

    // bottom layer doing login event
    if (code == NotLogin)
        return;

    // package decode error!
    if (code == Error){
        std::cout << "detect frame error!"<< std::endl;
        return;
    }

    // real event
    if (code == Normal){
        if (handler->whatAction() == SendMessageSingle){ // send message mode
            handler->sendMsg(_users, handler->getTargetID(), handler->getRawMsg());
        }

    }
}





