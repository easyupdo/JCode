#include <thread>
#include <iostream>

void ThreadFun(){
    std::cout<<"ThreadFun"<<std::endl;
}

int main(int argc,char** argv) {

    std::thread th1(ThreadFun);

    th1.join();
    
    return 0;
}