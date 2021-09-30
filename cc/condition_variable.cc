#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <atomic>
#include <functional>
#include <future>

std::mutex g_mx;
std::condition_variable g_cv;

int g_num = 0;
bool flag = false;
int main(int argc,char **argv) {

    auto func1 = [](){
        std::cout<<"thread func1"<<std::endl;
        
        while(true) {
            // if(!flag) {
                {

                    std::unique_lock<std::mutex>locker(g_mx);
                    // std::cout<<"func1 locker"<<std::endl;
                    if (g_num <= 5) {
                        g_num += 1 ;
                        std::cout<<"func1 g_num +1 :"<<g_num<<std::endl;
                    }else {
                        std::cout<<"### func1 notify:"<<g_num<<std::endl;
                        g_cv.notify_all();
                        // flag = true;
                    }
                }
                sleep(1);
                
            // }
        }

    };

    auto func2 = [](){
        std::cout<<"thread func2"<<std::endl;

        while(true) {
            // if(!flag) {
                {
                    std::unique_lock<std::mutex>locker(g_mx);
                    std::cout<<"func2 locker cv wait"<<std::endl;
                    g_cv.wait(locker);
                    if (g_num > 0) {
                        g_num -= 1 ;
                        std::cout<<"func2 g_num -1 :"<<g_num<<std::endl;
                    }else {
                        std::cout<<"### func2 g_num:"<<g_num<<std::endl;
                    }
                }
                sleep(1);
            // }
        }
    };

    // std::thread th1(func1);
    // std::thread th2(func2);
    
    // // th1.join();
    // // th2.join();

    std::atomic_int aint {0};
    // std::thread th3([&](){
    //     aint += 1;
    //     std::cout<<"aint:"<<aint<<std::endl;
    // });

    // std::thread th4([&](){
    //     std::cout<<"aint:"<<aint<<std::endl;
    // });
    // th3.join();
    // th4.join();

    std::future<int> fut = std::async([]()->int{
        std::cout<<"async"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return 111;
    });

    std::cout<<"async return:"<<fut.get()<<std::endl;

    std::promise<int> pro;
    std::future<int> f = pro.get_future();

    std::thread th8([](std::future<int>&f){
        std::cout<<"get future value:"<<f.get()<<std::endl;

    },std::ref(f));

    pro.set_value(999);

    th8.join();

    // std::packaged_task<>

    




 
    

    return 0;
}