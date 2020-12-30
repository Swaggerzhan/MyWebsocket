//
// Created by swagger on 2020/12/27.
//

#ifndef MYWEBSOCKET2_USERMAP_H
#define MYWEBSOCKET2_USERMAP_H


#include <iostream>
#include <map>
#include "utility.h"
#include "UserHandler.h"


class UserMap{


private:


    //        fd
    std::map<int, UserHandler*> _users;


public:

    /**
     * use fd to find UserHandler and return
     * @param fd
     * @return UserHandler*
     */
    UserHandler* findByFD(int fd);

    /**
     * use id find UserHandler and return
     * @param id
     * @return UserHandler*
     */
    UserHandler* findByID(int id);


    /**
     *  add user to map
     **/
    bool add(int fd);

    /**
     *  use id return fd
     *  @param id  (int)  user id
     *
     **/
    int findUserFDbyID(int id);

    /**
     * delete user
     *
     **/
    bool del(int fd);



};








#endif //MYWEBSOCKET2_USERMAP_H
