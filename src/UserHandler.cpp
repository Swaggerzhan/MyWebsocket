//
// Created by swagger on 2020/12/29.
//


#include "../include/UserHandler.h"
#include "../include/UserMap.h"



UserHandler::UserHandler(int fd){
    _handler = new WebsocketHandler(fd);
}


void UserHandler::sendMsg(UserMap* user, int target_id, std::string raw_msg){
    // package json
    std::string json_msg = _jsonCrypto.encode(
            _id,
            _name,
            target_id,
            raw_msg
    );
    int target_fd = user->findUserFDbyID(target_id);
    if (target_fd == -1){
        std::cout << "user not login now!" << std::endl;
        return;
        //todo.....
    }
    std::cout << "raw_msg: " << raw_msg << std::endl;
    std::cout << "json_msg: " << json_msg << std::endl;
    _handler->sendMsg(target_fd, json_msg);
}




RecvCode UserHandler::recvMsg(UserMap* user, int client_fd){
    clearBuff(); // clear buff
    RecvCode code = _handler->recvMsg(client_fd);
    if (code == CloseEvent){
        // sign from websocket layer mean close event;
        return CloseEvent;
    }

    if (code == NotHandshake)
        return NotHandshake;


    if (code == Normal){
        if ( !_isLogin ){ // not login
            // try to login

            std::cout << "try to login..." << std::endl;
            PackageType login_status = handleLogin(user);
            if( login_status == LoginSuccess){
                setLogin(); 
                std::cout << "login success" << std::endl;
                return NotLogin;
            }
            if ( login_status == LoginConflict){
                std::cout << "login conflict" << std::endl;
                return NotLogin;
            } 

            std::cout << "login fail" << std::endl;
            return NotLogin;

        }else{
            //clear data for new request!
            _target_id = -1;
            _action = NoneAction;
            memset(_raw_msg_buf, 0, BUF_SIZE);
            // real client even
            // decode data and tell upper layer done!
            if (_jsonCrypto.decode(_handler->websocket_frame_to_json_pointer(), _target_id, _action, _raw_msg_buf) == -1){
                std::cout << "json decode wrong!!!" << std::endl;
                // todo
            }
            return Normal;
        }
    }
    return Error;

}


int UserHandler::retID(){ return _id; }


void UserHandler::clearBuff(){
    memset(_raw_msg_buf, 0, BUF_SIZE);
    //_target_id = -1;
    //_action = NoneAction;
}


PackageType UserHandler::whatAction(){ return _action; }


int UserHandler::getTargetID(){ return _target_id; }



std::string UserHandler::getRawMsg(){
    std::string ret = _raw_msg_buf;
    return ret;
}

void UserHandler::setLogin(){ _isLogin = true;}



PackageType UserHandler::handleLogin(UserMap* user){
    std::cout << "_handler:" << _handler->websocket_frame_to_json_pointer() << std::endl;
    int flag = _jsonCrypto.decodeLoginPackage(_handler->websocket_frame_to_json_pointer(), _id, _name);
    UserHandler* another_handler = user->findByID(_id);
    // if another_handler has object mean id already login now!
    if (another_handler && another_handler->isLogin()){
        return LoginConflict;
    }







    if (flag){
        // decode success;
        sendLoginSuccessOrFail(true);

        return LoginSuccess;
    }
    sendLoginSuccessOrFail(false);
    return LoginFail;

}


void UserHandler::sendLoginSuccessOrFail(bool flag){
    clearBuff();
    if (flag){
        std::cout << "sending success login package" << std::endl;
        _jsonCrypto.LoginSuccess(_raw_msg_buf);
        std::string msg = _raw_msg_buf;
        _handler->sendMsg(-1, msg);
        return;
    }
    std::cout << "sending fail login package" << std::endl;
    _jsonCrypto.LoginFail(_raw_msg_buf);
    std::string msg = _raw_msg_buf;
    _handler->sendMsg(-1, msg);
}



bool UserHandler::isLogin(){ return _isLogin; }