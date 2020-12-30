//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_USERHANDLER_H
#define MYWEBSOCKET2_USERHANDLER_H

#include <iostream>
#include "utility.h"
#include "WebsocketHandler.h"
#include "JsonCrypto.h"

class UserMap;


class UserHandler{

private:

    int _id = -1;

    char _name[NAME_LEN];

    bool _isLogin = false;

    WebsocketHandler* _handler;

    JsonCrypto _jsonCrypto;

    //UserMap* _users;

//----------------------------------

    char _raw_msg_buf[BUF_SIZE];

    int _target_id = -1;

    PackageType _action = NoneAction;

//----------------------------------

public:

    /**
     *  object injection
     **/
    UserHandler(int fd);

    /**
     *  send msg
     **/
    void sendMsg(UserMap* userMap, int target_id, std::string raw_msg);

    /**
     * recv message
     * @param client_fd
     * @return RecvCode to upper layer
     */
    RecvCode recvMsg(UserMap* user, int client_fd);

    /**
     *
     * @return _id
     */
    int retID();

    /**
     * clear buff
     */
    void clearBuff();

    /**
     *
     * @return _action
     */
    PackageType whatAction();

    /**
     *
     * @return _target_id
     */
    int getTargetID();


    /**
     * return raw message
     * @return std::string
     */
    std::string getRawMsg();

    /**
     * set _isLogin = true
     */
    void setLogin();

    /**
     * handler user layer login event
     * @return RecvCode
     */
    PackageType handleLogin(UserMap* user);

    /**
     * send login message to client
     * @param flag true for login success and false for login fail
     */
    void sendLoginSuccessOrFail(bool flag);

    /**
     *  return _isLogin 
     **/
    bool isLogin();

};



#endif //MYWEBSOCKET2_USERHANDLER_H
