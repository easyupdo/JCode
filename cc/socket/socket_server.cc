#include "log.hpp"
#include "tcpsocket.h"


int main(int argc,char ** argv) {

    // InitLog("log.log",LogMode::kFile);
    // gets();




    // ServerUdpSocket server;
    // server.Init("server");  
    // server.Start();

    ServerTcpSocket server;
    server.Init();  
    server.Start();


    return 0;
}