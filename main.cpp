#include <iostream>
#include "include/InterFace.h"



int main() {

    UserMap* map = new UserMap();
    InterFace s(map);
    s.RUN();

}
