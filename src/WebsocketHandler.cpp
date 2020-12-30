//
// Created by swagger on 2020/12/29.
//

#include "../include/WebsocketHandler.h"


WebsocketHandler::WebsocketHandler(int fd){
    _fd = fd;
}


void WebsocketHandler::sendMsg(int target_fd, std::string msg){

    if (target_fd == -1)
        target_fd = _fd;

    // clean buf data
    //memset(_msg_buf, 0, BUF_SIZE);

    char _tmp[BUF_SIZE];
    memset(_tmp, 0, BUF_SIZE);

    std::cout << "before makeFrame: " << msg << std::endl;

    int websocket_frame_len = _websocketCrypto.makeFrame(TEXT_FRAME,
                               (unsigned char*)msg.c_str(),
                               msg.length(),
                               (unsigned char*)_tmp,
                               BUF_SIZE
    );

    std::cout << "after makeFrame: " << _tmp << std::endl;
    std::cout << "real websocketFrame len: " << websocket_frame_len << std::endl;
    std::cout << "fake websocketFrame len: " << strlen(_tmp) << std::endl;


    std::string out(_tmp, websocket_frame_len);
    std::cout << "websocket msg: " << out << std::endl;
    tcpHandler.sendMsg(target_fd, out);

}

bool WebsocketHandler::isHandshake(){ return _isHandshake; }


void WebsocketHandler::setHandshaked(){ _isHandshake = true; }


RecvCode WebsocketHandler::recvMsg(int client_fd){

    // clear buff
    clearBuff();
    int _msg_buf_len = -1;
    RecvCode code = tcpHandler.recvMsg(client_fd, _msg_buf, _msg_buf_len);
    if (code == CloseEvent){
        //sign from tcp layer    mean close event
        // destroy this
        return CloseEvent;
    }

    if (code == Normal ){
        if ( !_isHandshake ){ // not handshake yet
            if (OPENING_FRAME == _websocketCrypto.parseHandshake(_msg_buf, strlen(_msg_buf))){
                std::string ansMsg = _websocketCrypto.answerHandshake();
                tcpHandler.sendMsg(client_fd, ansMsg);
            }
            setHandshaked(); // set login
            return NotHandshake;
        }else{
            /* 
            
            already handshaked

            */
            int out_size;
            // decode websocket frame

            std::cout << "correct len: " << _msg_buf_len << std::endl;


            WebSocketFrameType type =  _websocketCrypto.getFrame((unsigned char*)_msg_buf, 
                _msg_buf_len,
                (unsigned char*)_msg_buf_decode, 
                BUF_SIZE, 
                &out_size);
            // remote client try to close
            if (type == CLOSING_FRAME){
                tcpHandler.close_fd(_fd);
                return CloseEvent;
            }

            if (type == ERROR_FRAME){
                std::cout << "error frame" << std::endl;
                tcpHandler.close_fd(_fd);
                return CloseEvent;
            }


            std::cout << "json: " <<_msg_buf_decode << std::endl;
                

            return Normal;
        }
    }else{
        return Error;
    }

}


char *WebsocketHandler::websocket_frame_to_json_pointer(){ return _msg_buf_decode; }

char* WebsocketHandler::websocket_buf_pointer(){return _msg_buf;}


void WebsocketHandler::clearBuff(){ 
    memset(_msg_buf, 0, BUF_SIZE); 
    memset(_msg_buf_decode, 0, BUF_SIZE);
}