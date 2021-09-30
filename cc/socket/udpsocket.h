#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_

#include "util.h"
#include "log.hpp"
#include <sys/ioctl.h>
#include <iostream>
#include <sys/socket.h>
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



class UdpSocket {
    public:
    UdpSocket(){}
    bool Init(const std::string &type) {
        socket_ = socket(AF_INET,SOCK_DGRAM,0);
        if(socket_ == -1) {
            LogDebug << "udp socket create failed! error code:"<<errno<<" error code string:"<< strerror(errno);
            return false;
        }
        LogDebug<<"udp socket create success" <<"[socket:"<<socket_<<"]";
        
        addr_.sin_family = AF_INET;//ipv4
        addr_.sin_port = htons(atoi(port_.c_str()));
        
        if(type == "client") {
            addr_.sin_addr.s_addr = inet_addr("172.16.11.255"); //client broadcast
        }else if(type == "server") {
            addr_.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        

        bzero(&(addr_.sin_zero),sizeof(addr_.sin_zero));

        
        return true;
    }

    private:
    protected:
        struct sockaddr_in addr_;
        int socket_;
        std::string port_ = "13400";
};



class ServerUdpSocket : public UdpSocket {
    public:
    ServerUdpSocket(){}
    bool Start() {
        int opt;
        if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0)
        {           
            LogDebug <<"udp socket setsockopt failed ! error code:"<<errno << " error code string:"<< strerror(errno);
            return false;
        }

        int ret = bind(socket_, (struct sockaddr *)&addr_, sizeof(addr_));
        if(ret < 0) {
            LogDebug <<"udp socket bind failed ! error code:"<<errno << " error code string:"<< strerror(errno);
            return -1;
        }
       
        //tragger socket
        char recv_buff[100];
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);

        while(1) {
            bzero(recv_buff,100);
            LogDebug <<"Server Online ... [port:"<<port_<<"]";
            int readedBytes = recvfrom(socket_, recv_buff, sizeof(recv_buff), 0, (struct sockaddr *) &client_addr, &len);
            char client_ip[20];
            inet_ntop(AF_INET,&(client_addr.sin_addr), client_ip, sizeof(client_ip));
            int client_port = ntohs(client_addr.sin_port);
            LogDebug<<"udp received " <<"[ip:"<<std::string(client_ip)<<"][port:"<<client_port<<"]"<<"[socket:"<<tcp_socket_conn_<<"]";
            LogDebug<<"udp recv data:["<<recv_buff<<"]";
            HexOut(recv_buff,0,8,"header");
            // std::vector<unsigned char> msg = std::move(VehicleIdentificationRespons());
            std::vector<unsigned char> msg;
            unsigned char msg_c[msg.size()];


            int send_num = sendto(socket_, &msg[0], msg.size(), 0, (struct sockaddr *)&client_addr, sizeof(client_addr)); 
            if(send_num) {
                LogDebug << "Respons size:["<<send_num<<"] Header:";
                HexOut(recv_buff,0,8,"header");
            }
        }
    
        return true;
    }
    private:
        int tcp_socket_conn_;
        int tcp_socket_select_;
        fd_set socket_set_,select_set_;


};

class ClientUdpSocket : public UdpSocket {
    public:
    ClientUdpSocket() {}
    void Start() {
        // while(1) {
            std::string send_str = "Hello"; 
            int send_num = sendto(socket_, send_str.c_str(), send_str.length(), 0, (struct sockaddr *)&addr_, sizeof(addr_)); 
            LogDebug << "udp send data:["<<send_str<<"] send_data_size:["<<send_num<<"]";
        // }
    }

    // send ip VehicleIdentificationRequest
    void SendVehicleIdentificationRequest(const std::string &ip) {
        //TODO doip
        addr_.sin_addr.s_addr = inet_addr(ip.c_str()); //client broadcast

        // std::vector<unsigned char> vir = VehicleIdentificationRequest();
        std::vector<unsigned char>vir;

        int send_num = sendto(socket_, &vir[0], vir.size(), 0, (struct sockaddr *)&addr_, sizeof(addr_)); 
        if(send_num <= 0) {
            LogDebug <<"sendto is error! error_code:"<<errno<<"error_code_data:"<<strerror(errno);
        } else {
            LogDebug << "udp send data: send_data_size:["<<send_num<<"]";
        }

        //Test Response
        socklen_t len = sizeof(addr_);
        char recv_buff[100] = {0};
        int readedBytes = recvfrom(socket_, recv_buff, sizeof(recv_buff), 0, (struct sockaddr *) &addr_, &len);
        if(readedBytes) {
            LogDebug << "VehicleIdentificationRespons: size:["<<readedBytes<<"]";
            HexOut(recv_buff,0,8,"Header");
            CharOut(recv_buff,8,25,"VIN");
            HexOut(recv_buff,25,27,"LogicalAddress");
            CharOut(recv_buff,27,33,"EID");
            CharOut(recv_buff,33,39,"GID");
            HexOut(recv_buff,39,40,"FAC");
            HexOut(recv_buff,40,41,"SYNC");

            LogDebug<<"VehicleIdentificationRespons Over!";    
        }
    }

    bool Connect(); 
    protected:
    private:


};


#endif //_UDP_SOCKET_H_