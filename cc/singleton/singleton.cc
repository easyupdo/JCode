#include <iostream>
#include <thread>

class Singleton{
    public:
    Singleton(Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton operator=(Singleton&) = delete;
    Singleton operator=(Singleton&&) =delete;

    // c++11 last is safe
    static Singleton & GetInstance() {
        static Singleton instance;
        return instance;
    }

    int SetAndGet(){
        this->num += 1;
        return this->num;
    }

    private:
    Singleton(){}

    int num {0};

    
};


int main(int argc,char **argv) {

    std::thread th1([&]() {
        while(1) {
            // std::cout<<"th1"<<std::endl;
            std::cout<<"Th1:"<<Singleton::GetInstance().SetAndGet()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    
    std::thread th2([&]() {
        while(1) {
            // std::cout<<"th2"<<std::endl;
            std::cout<<"Th2:"<<Singleton::GetInstance().SetAndGet()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    th1.join();
    th2.join();
    

    return 0;
}