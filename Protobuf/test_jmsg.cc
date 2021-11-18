#include <iostream>
#include "msg.pb.h"

int main(int argc,char**argv) {
    JMSG jmsg;
    jmsg.set_name("Jay");
    std::string s_str;
    jmsg.SerializeToString(&s_str);

    std::cout<<"s_str:"<<s_str<<std::endl;
    return 0;
}