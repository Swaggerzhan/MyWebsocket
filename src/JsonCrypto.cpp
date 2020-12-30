//
// Created by swagger on 2020/12/29.
//

#include "../include/JsonCrypto.h"
#include "../include/utility.h"


std::string JsonCrypto::encode(int source_id, char* source_name, int target_id, std::string raw_msg){
    Json::Value root;
    root["source_id"] = source_id;
    root["source_name"] = source_name;
    root["des_id"] = target_id;
    root["message"] = raw_msg.c_str();
    root["time"] = 11111111;
    return root.toStyledString();
}


int JsonCrypto::decode(char* msg_buf, int &target_id, PackageType &type, char* raw_msg_buf){
    Json::Reader reader(Json::Features::strictMode());
    Json::Value value;
    if (!reader.parse(msg_buf, value))
        return -1;
    type = (PackageType)value["type"].asInt();
    target_id = value["des_id"].asInt();
    std::string msg = value["message"].asString();
    memcpy(raw_msg_buf, msg.c_str(), msg.length());
    return 1;
}


int JsonCrypto::decodeLoginPackage(char* msg_buf, int &id, char* name){
    Json::Reader reader(Json::Features::strictMode());
    Json::Value value;
    if (!reader.parse(msg_buf, value)){
        std::cout << "parse fail!" << std::endl;
        return -1;
    }
        

    
    std::cout << msg_buf << std::endl;

    // if (!checkLoginPackage(value))
    //     return -1;
    
    id = value["id"].asInt();
    std::string msg = value["name"].asString();


    std::cout << "decode: " << std::endl;
    std::cout << "id: " << id << " name: " << msg << std::endl;
    
    memcpy(name, msg.c_str(), msg.length());
    return 1;
}

bool JsonCrypto::checkLoginPackage(Json::Value value){
    if (!value["id"].isInt() || !value["name"].asCString())
        return false;
    return true;
}




void JsonCrypto::LoginSuccess(char* msg_buf){
    Json::Value root;
    //root["type"] = LoginSuccess;
    root["type"] = 3;
    root["message"] = "handshake success!";
    std::string out = root.toStyledString();
    //std::cout << out << std::endl;
    memcpy(msg_buf, out.c_str(), out.length());
}


void JsonCrypto::LoginFail(char* msg_buf){
    Json::Value root;
    //root["type"] = (int)LoginFail;
    root["type"] = -1;
    root["message"] = "handshake fail!";
    std::string out = root.toStyledString();
    //std::cout << out << std::endl;
    memcpy(msg_buf, out.c_str(), out.length());
}
