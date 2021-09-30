#include "tcpsocket.h"

bool TcpSocket::Init(){
    tcp_socket_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(tcp_socket_ == -1) {
        LogDebug << "tcp socket create failed! error code:"<<errno<<" error code string:"<< strerror(errno);
        return false;
    }
    LogDebug<<"tcp socket create success" <<"[socket:"<<tcp_socket_<<"]";
    
    addr_.sin_family = AF_INET;//ipv4
    addr_.sin_port = htons(atoi(port_.c_str()));
    // addr_.sin_addr.s_addr = inet_addr(ip_.c_str());

    if(inet_pton(AF_INET,ip_.c_str(),&(addr_.sin_addr)) < 0) {
        LogDebug <<"tcp socket inet_pton faild! error code:"<<errno<<" error code string:"<< strerror(errno) <<"[ip:"<<ip_<<"]";
        return false;
    }
    bzero(&(addr_.sin_zero),sizeof(addr_.sin_zero));
    
    return true;
}

TcpSocket::TcpSocket(std::string &ip,std::string &port){
}


ServerTcpSocket::ServerTcpSocket() : TcpSocket(),
    tcp_socket_conn_(-1),
    tcp_socket_select_(-1) {
    std::thread recv_thread([&]() {
        char ch[100];
        while(1) {
            bzero(&ch,100);
            if(is_recv_ && (tcp_socket_select_ > 0)) {
                LogDebug<<"recv_thread tcp_socket_select_:["<<tcp_socket_select_<<"]";
                int bytes = recv(tcp_socket_select_,ch,100,0);
                if(bytes <= 0) {
                    LogDebug<<"Client tcp socket close!";
                    {
                        std::lock_guard<std::mutex>locker(mx_);
                        FD_CLR(tcp_socket_select_,&socket_set_);
                    }
                    tcp_socket_select_ = -1;
                    
                    continue;
                }
                is_recv_ = false;
                LogDebug <<"client recv:"<<ch << "size:"<<strlen(ch) ;
                HexOut(ch,0,8,"Header");
                std::vector<std::vector<unsigned char>> r_msgs = ResponseMsg(ch,bytes,NULL);
                
                for(auto r_msg : r_msgs) {
                    int len = send(tcp_socket_select_,&r_msg[0],r_msg.size(),0);
                    if(len) {
                        LogDebug << "server send size:"<<len;
                        is_send_ = false;
                    }
                }



                // if()

                LogDebug << "Test Send";
                is_send_ = true;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread send_thread([&]() {
        char ch[100];
        while(1) {
            bzero(&ch,100);
            if(is_send_ && (tcp_socket_select_ >=0)) {
                #ifdef JDebug
                    LogDebug<<"send_thread: tcp_socket_select_:"<<tcp_socket_select_;
                #endif
                std::string h = "hello";
                //RoutingActivationResponse
                // std::vector<unsigned char> msg = RoutingActivationRespons();
                std::vector<unsigned char>msg;
                
                int len = send(tcp_socket_select_,&msg[0],msg.size(),0);
                if(len) {
                    LogDebug << "server send size:"<<len<<"str:"<<h;
                    is_send_ = false;
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    recv_thread.detach();
    send_thread.detach();
}

bool ServerTcpSocket::Start() {
    int opt;
    if (setsockopt(tcp_socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0)
    {           
        LogDebug <<"tcp socket setsockopt failed ! error code:"<<errno << " error code string:"<< strerror(errno);
        return false;
    }

    int ret = bind(tcp_socket_, (struct sockaddr *)&addr_, sizeof(addr_));
    if(ret < 0) {
        LogDebug <<"tcp socket bind failed ! error code:"<<errno << " error code string:"<< strerror(errno);
        return -1;
    }
    LogDebug<<"tcp bind success !";
    // int listen(int sockfd, int backlog);
    if(listen(tcp_socket_,5) < 0) {
        LogDebug<<"tcp socket listen failed ! error code:"<<errno << " error code string:"<< strerror(errno);
        return false;
    }
    LogDebug<<"tcp listening ..." <<"[ip:"<<ip_<<"][port:"<<port_<<"]";
    FD_ZERO(&socket_set_);
    // FD_SET(0,&socket_set_);
    FD_SET(tcp_socket_,&socket_set_);
    while(1) {
        {
            std::lock_guard<std::mutex>locker(mx_);
            select_set_ = socket_set_;
        }
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
 
        int ret = select(FD_SETSIZE,&select_set_,NULL,NULL,NULL);
        if(ret < 1) {
            LogDebug << "server select error! exit";
            exit(1);
        }

        for (int fd = 0;fd < FD_SETSIZE;++fd) {
            // LogDebug <<"FOR FD:"<<fd;
            if(FD_ISSET(fd,&select_set_)) {
                // LogDebug <<"##### FD:"<<fd;
                if(fd == tcp_socket_) {
                    
                    // accept
                    struct sockaddr_in client_addr;
                    socklen_t len = sizeof(client_addr);
                    if((tcp_socket_conn_ = accept(tcp_socket_,(struct sockaddr*)&client_addr,&len)) == -1) {

                        LogDebug <<"tcp accept failed ! error code:"<<errno << " error code string:"<< strerror(errno);
                        // return false;
                    }else {
                        // add new conn_socket_;
                        {
                            std::lock_guard<std::mutex>locker(mx_);
                            FD_SET(tcp_socket_conn_,&socket_set_);
                        }
                       
                        char client_ip[20];
                        inet_ntop(AF_INET,&(client_addr.sin_addr), client_ip, sizeof(client_ip));
                        int client_port = ntohs(client_addr.sin_port);
                        LogDebug<<"tcp accept ..." <<"[ip:"<<std::string(client_ip)<<"][port:"<<client_port<<"]"<<"[tcp_socket_conn:"<<tcp_socket_conn_<<"]";
                    }
                }else {
                    //tragger socket
                    is_recv_ = true;
                    tcp_socket_select_ = fd;
                    // LogDebug<<"Can Read socketfd :["<<fd<<"]";
                }
            }
        }       
    }

    return true;
}

// ### Client 
ClientTcpSocket::ClientTcpSocket() : TcpSocket() {
    oc_.opt = Options::Off;
}

 void ClientTcpSocket::Start() {
    
    std::thread control_thread([&](){
        while(1) {
            LogDebug<<"Client Please select options";
            LogDebug<<"S:send  R:recv  A:VehicleIdentificationRequest; B:RoutingActivationRquest; C:DiagnosticRequest" ;
            char in[10] = {0};
            std::cin.getline(in,10);
            {
                std::lock_guard<std::mutex>locker(mx_);
                if(std::string(in) == "S") {
                    oc_.opt = Options::Send;
                    LogDebug<<"Pleas input send data";
                    std::cin.getline(oc_.buff,100);
                    LogDebug << "Input data :" << oc_.buff;
                }else if(std::string(in) == "R") {
                    oc_.opt = Options::Redv;
                    LogDebug << "Recving ...";
                    bzero(oc_.buff,0);
                }else if(std::string(in) == "B") {
                    SendRoutingActivationRequest();
                    // oc_.opt = Options::Redv;
                }else if(std::string(in) == "C")
                    SendDiagnosticRequest();
            }
            LogDebug <<"Control:oc:"<<(int)oc_.opt;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });
    

    std::thread connect_thread([&]() {
        bool status = Connect();
    });
    std::thread recv_thread([&]() {
        while(1) {
            if(is_connect_) {
                #ifdef JDebug
                    LogDebug << "recv oc:"<<(int)oc_.opt;
                #endif
                {
                    std::lock_guard<std::mutex>locker(mx_);
                    #ifdef JDebug
                        LogInfo << "Recv get mx_";
                    #endif
                    if(oc_.opt == Options::Redv){
                        
                        
                        LogDebug << "client ready recv!";
                        int len = recv(tcp_socket_,oc_.buff,100,0);
                        LogDebug <<"client recv:"<<oc_.buff;

                        // SWITCH
                        HexOut(oc_.buff,0,8,"Header");
                        HexOut(oc_.buff,8,10,"UpLogicalAddress");
                        HexOut(oc_.buff,10,12,"EntityLogicalAddress");
                        HexOut(oc_.buff,12,13,"ResNum");
                        HexOut(oc_.buff,13,17,"ISO");



                        //updata oc
                        oc_.opt = Options::Off;
                        bzero(oc_.buff,sizeof(oc_.buff));
                        
                        
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    });
    std::thread send_thread([&]() {
        while(1) {
            if(is_connect_) {
                {
                    std::lock_guard<std::mutex>locker(mx_);
                    #ifdef JDebug
                        LogInfo << "Send get mx_ : send oc:"<<(int)oc_.opt;
                    #endif
                    if(oc_.opt == Options::Send) {
                        {
                            int bytes = send(tcp_socket_,oc_.buff,sizeof(oc_.buff),0);
                            LogDebug <<"tcp socket send size:"<<bytes << "str:" << oc_.buff;

                            //update oc
                            oc_.opt = Options::Off;
                            bzero(oc_.buff,sizeof(oc_.buff));
                        }
                        
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    });
    //join
    connect_thread.join();
    // send_thread.join();
    recv_thread.join();
    control_thread.join();
}


bool ClientTcpSocket::Connect(){
    //int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    /*
    //no black socket
    fd_set socket_set;
    timeval timeout;
    timeout.tv_sec=1;
    timeout.tv_usec = 0;
    FD_ZERO(&socket_set);
    FD_SET(tcp_socket_,&socket_set);

    int ret = connect(tcp_socket_,(struct sockaddr*)&addr_,sizeof(addr_));
    if(ret == 0) { //success
        //
    }else if(errno != EINPROGRESS) {
        LogDebug <<"unblock connect failed!";
    }else if(errno == EINPROGRESS) {
        LogDebug <<"unblock connecting ...";
    }

    int s_ret = select(tcp_socket_ + 1,NULL,&socket_set,NULL,&timeout);

    if(s_ret <=0) {
        LogDebug <<" connection time out";
    }
    if(! FD_ISSET(tcp_socket_,&socket_set)) {
        LogDebug <<"tcp_socket no event ";
    }else{
        LogDebug << "tcp socket connect ! [ip:"<<ip_<<"][port:"<<port_<<"]";
        is_connect_ = true;
    }
    */


    std::lock_guard<std::mutex>locker(mx_);
    if(connect(tcp_socket_,(struct sockaddr*)&addr_,sizeof(addr_)) < 0) {
        LogDebug << "tcp socket connect failed ! error code:"<<errno << " error code string:"<< strerror(errno);
        return false;
    }
    LogDebug << "tcp socket connect ! [ip:"<<ip_<<"][port:"<<port_<<"]";
    is_connect_ = true;
}