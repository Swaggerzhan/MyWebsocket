//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_UTILITY_H


#define BUF_SIZE 2048
#define NAME_LEN 32
#define OPEN_MAX 50
#define LISTEN_SIZE 50


enum WebSocketFrameType {
    ERROR_FRAME=0xFF00,
    INCOMPLETE_FRAME=0xFE00,

    OPENING_FRAME=0x3300,
    CLOSING_FRAME=0x3400,

    INCOMPLETE_TEXT_FRAME=0x01, // there has more
    INCOMPLETE_BINARY_FRAME=0x02, // there has more

    TEXT_FRAME=0x81,
    BINARY_FRAME=0x82,

    PING_FRAME=0x19,
    PONG_FRAME=0x1A
};


enum PackageType{
    LoginFail = -1,
    LoginSuccess = 3,
    LoginConflict = 4,
    // 1 and 2 was reserve
    SendMessageSingle = 11,
    ErrorPackage = 255,
    NoneAction = 1111
};


enum RecvCode{
    NotHandshake = 1,
    NotLogin = 2,
    CloseEvent = 3,
    Error = 4,

    Normal = 5,


};





#define MYWEBSOCKET2_UTILITY_H

#endif //MYWEBSOCKET2_UTILITY_H
