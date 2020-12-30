//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_JSONCRYPTO_H
#define MYWEBSOCKET2_JSONCRYPTO_H



#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include "utility.h"
#include <cstring>

using namespace Json;


/**
 *  this class has only one object
 *  init() will clear all private data
 *
 **/

class JsonCrypto{


public:


    bool checkLoginPackage(Json::Value value);

    /**
     * encode json package
     * @param source_id
     * @param source_name
     * @param target_id
     * @param raw_msg
     * @return
     */
    std::string encode(int source_id, char* source_name, int target_id, std::string raw_msg);

    /**
     * decode json package
     * @param msg_buf    json format message
     * @param target_id
     * @param type
     * @param raw_msg_buf raw message
     * @return
     */
    int decode(char* msg_buf, int &target_id, PackageType &type, char* raw_msg_buf);

    int decodeLoginPackage(char* msg_buf, int &id, char* name);


    void LoginSuccess(char* msg_buf);

    void LoginFail(char* msg_buf);



//    /**
//     *  decoder package return ID
//     *  @return (int) id
//     **/
//    int getID(char *msg, int msg_len){
//        clearBuff();
//        if (!_reader.parse(msg, _value))
//            return -1;
//        return _value['id'].asInt();
//    }
//
//
//
//    int getTargetID(char *msg, int msg_len){
//        clearBuff();
//        if (!_reader.parse(msg, _value))
//            return -1;
//        return _value['des_id'].asInt();
//    }
//
//
//
//    /**
//     * decoder package return Name
//     * @return (string) name
//     **/
//    std::string getName(char *msg, int msg_len){
//        clearBuff();
//        if (!_reader.parse(msg, _value))
//            return nullptr;
//        return _value['name'].asString();
//    }
//
//
//    /**
//     * decoder package return message
//     * @return (string) message
//     **/
//    std::string getRawMsg(char *msg, int msg_len){
//        clearBuff();
//        if (!_reader.parse(msg, _value))
//            return nullptr;
//        return _value['msg'].asString();
//    }
//
//    /**
//     *  parse package type
//     *  @param msg_buf (char*) json data buf
//     *  @param msg_buf_len (int) msg_buf_len
//     *
//     **/
//    PackageType getPackageType(char *msg_buf, int msg_buf_len){
//        clearBuff();
//        if (! _reader.parse(msg_buf, _value))
//            return ErrorPackage;
//        return (PackageType)_value["type"].asInt();
//    }
//
//
//
//    /**
//     * @param type (PackageType)
//     * @param raw_msg (char*) text message
//     * @param raw_msg_len (int) raw_msg len
//     * @param msg_buf (char*) json message
//     * @param msg_buf_len (int) msg_buf len
//     * @param target (int) target id    not use for 0
//     * @param source_id (int) source id not use for 0
//     * @param name (char*) source name  not use for null
//     * @param name_len (int) name len   not use for 0
//     *
//     **/
//    void makePackage(PackageType type,
//                     char *raw_msg,
//                     int raw_msg_len,
//                     char* msg_buf,
//                     int msg_buf_len,
//                     int target,
//                     int source_id,
//                     char *name,
//                     int name_len
//    ){
//        Json::Value root;
//
//        std::string out;
//
//        if (type == LoginSuccess){
//            root["type"] = 3;
//            root["message"] = "handshake success!";
//            out = root.toStyledString();
//            memcpy(msg_buf, out.c_str(), out.length());
//            return;
//        }
//        if (type == LoginFail){
//            root["type"] = -1;
//            root["message"] = "handshake failed!";
//            out = root.toStyledString();
//            memcpy(msg_buf, out.c_str(), out.length());
//            return;
//        }
//
//        if (type == SendMessageSingle){
//            root["source_id"] = source_id;
//            root["source_name"] = name;
//            root["des_id"] = target;
//            root["message"] = raw_msg;
//            root["time"] = 99999999;
//            root["type"] = 1;
//            out = root.toStyledString();
//            memcpy(msg_buf, out.c_str(), out.length());
//            return;
//        }
//    }
//


};






#endif //MYWEBSOCKET2_JSONCRYPTO_H
