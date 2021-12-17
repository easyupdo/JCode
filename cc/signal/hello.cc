/*************************************************************************
    > File Name: hello.cc
    > Author: JayGuan
    > Mail: 
    > Created Time: Tue 14 Dec 2021 02:17:12 PM CST
 ************************************************************************/

#include<iostream>
#include <thread>
#include <chrono>
using namespace std;
int main(int argc,char * argv[])
{
  while(1){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"FUCK Hello!"<<std::endl;
  }
return 0;
}

