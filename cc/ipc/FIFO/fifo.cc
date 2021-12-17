#include <iostream>
#include <sys/stat.h>>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char**argv){

    std::string fifo_file= "./my_fifo";
    int fifo_fd = open(fifo_file.c_str(),O_RDONLY | O_NONBLOCK);
    std::cout<<"open:"<<fifo_fd<<std::endl;

    return 0;
}