//
// Created by swagger on 2020/12/29.
//


#include "../include/UserMap.h"


UserHandler* UserMap::findByFD(int fd){
    auto iter = _users.find(fd);
    if (iter != _users.end())
        return iter->second;
    return nullptr;
}


UserHandler* UserMap::findByID(int id){

    for (auto & _user : _users){
        if (_user.second->retID() == id)
            return _user.second;
    }
    return nullptr;
}


bool UserMap::add(int fd){
    _users.insert(std::pair<int, UserHandler*>(fd, new UserHandler(fd)));
    return true;
}


int UserMap::findUserFDbyID(int id){
    for (auto & _user : _users){
        if (_user.second->retID() == id) // find id return fd
            return _user.first;
    }
    return -1;
}


bool UserMap::del(int fd){
    auto iter = _users.find(fd);
    // item not exist!
    if (iter != _users.end())
        return false;
    delete iter->second;
    _users.erase(fd);
    return true;
}




