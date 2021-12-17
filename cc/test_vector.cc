#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <chrono>

#include <tuple>

std::condition_variable g_cv;
std::mutex g_mx;


#define pout(x) std::cout<<x<<std::endl;

void operator""_s(const char * name,size_t n) {
    std::this_thread::sleep_for(std::chrono::seconds(atoi(name)));
}

int FuckFunc(){
    throw "FuckYou";
    return 1;
}


int main(int argc,char **argv) {

    std::vector<char> ch_vec{};
    char * da ="Hello";
    ch_vec.insert(ch_vec.end(),da,da+5);

    std::vector<std::thread> vec;

    // send 5s
    vec.emplace_back([]{
        pout("th2 start!");
        "1"_s;
        g_cv.notify_one();
        pout("Notify One");
    });

    vec.emplace_back([]{
        pout("th1 start!");
        std::unique_lock<std::mutex> locker(g_mx);
        g_cv.wait(locker);
        pout("We got notify!");
    });


    for(auto &one : vec){
        one.join();
    }

    std::tuple<int,std::string> tp{std::make_tuple(123,"Hello")};
    
    std::get<0>(tp);
    
    std::thread thn;

    auto THFUNC = []() -> int {
        // throw "Fuck You";
        throw std::exception{};
        return 1;
    };

    try
    {
        int i = 0;
        // throw "FK";
        // THFUNC();
        FuckFunc();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    

    return 0;
}