#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#include "util.h"
#include "doipprotocol.h"
#include "log.hpp"
#include "sys/socket.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>
#include <iomanip>
#include <memory>
#include <string.h>
#include <errno.h>
#include <vector>
#include <thread>
#include<unistd.h>
#include <thread>
#include <mutex>
#include <map>

// #define JDebug

enum class Options: int8_t{
    Send = 1,
    Redv = 2,
    Off = 3
};

typedef struct OperationControl{
    Options opt;
    char buff[100] = {0};
}OperationControl;

class TcpSocket{
    public:
    TcpSocket(){}
    TcpSocket(std::string &ip,std::string &port);
    
    bool Init();

    protected:
        struct sockaddr_in addr_;
        int tcp_socket_;
        std::string port_ = "13400";
        std::string ip_ = "127.0.0.1";
    private:
};



class ServerTcpSocket : public TcpSocket {
    public:
    ServerTcpSocket();
    bool Start();
    private:
    int tcp_socket_conn_;
    int tcp_socket_select_;
    std::vector<std::unique_ptr<std::thread>> thread_pool_;
    OperationControl oc_;

    // std::map<std::string,int> conn_socket_map_;
    std::vector<int>vec_socket_;

    fd_set socket_set_,select_set_;

    bool is_recv_ = false;
    bool is_send_ = false;

    std::mutex mx_;

};

class ClientTcpSocket : public TcpSocket {
    public:
    ClientTcpSocket();

    void Start();
    
    bool Connect();

    void SendRoutingActivationRequest() {
        std::vector<unsigned char> msg;
        oc_.opt = Options::Send;
        LogDebug << "Sending ... RoutingActivationRequest";
        bzero(oc_.buff,0);
        memcpy(oc_.buff,&msg[0],msg.size());
    }

    void SendDiagnosticRequest() {
        std::vector<unsigned char> msg;
        oc_.opt = Options::Send;
        LogDebug << "Sending ... DiagnosticRequest";
        bzero(oc_.buff,0);
        memcpy(oc_.buff,&msg[0],msg.size());
    }

    protected:
    private:
    std::vector<std::shared_ptr<std::thread>> client_threads;
    bool is_connect_ = false;
    std::mutex mx_;
    OperationControl oc_;


};

#endif //_TCP_SOCKET_H_