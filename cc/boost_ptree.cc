#include <iostream>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include <sstream>
#include <boost/algorithm/hex.hpp>

#define pout(x) std::cout<<x<<std::endl;


int main(int argc,char**argv) {
    
    boost::property_tree::ptree conf;


    std::ifstream isf("./conf.json");
    if(isf.is_open()) {
        boost::property_tree::read_json(isf,conf);
    }else {
        pout("conf.json open is failed!");
    }

    std::string name = conf.get<std::string>("name");

    pout("name:"+name);


    auto child = conf.get_child("NetWork");
    std::string child_ip =  child.get<std::string>("local_ip");

    pout("child_ip:" + child_ip);


    for(auto one : conf.get_child("NetWork")) {
        pout(one.first);
        pout(one.second.data());
    }

    std::string ip = conf.get<std::string>("NetWork.local_ip");
    unsigned tcp_port = conf.get<unsigned>("NetWork.TcpPort");
    pout("local_ip:" + ip);
    pout("tcp_port:");
    pout(tcp_port);

    auto arr = conf.get_child("array");
    for(auto one : arr) {
        pout(one.first)
        pout(one.second.data())
    }




    char bytes[60]{}; 
    std::string hash = boost::algorithm::unhex(std::string("f180")); 
    std::copy(hash.begin(), hash.end(), bytes);


    
   


    return 0;
}