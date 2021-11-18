#include <iostream>


enum OT : uint8_t{
    kET = 0x01,
    kSB = 0x02
};

template <typename T>
class Temp {
    public:
    Temp(int a) :m_i(a){}

    void Test() {
        std::cout<<typeid(T).name()<<std::endl;
        std::cout<<typeid(OT::kET).name()<<std::endl;
        std::cout<<typeid(OT::kSB).name()<<std::endl;
        
    }

    private:
    int & m_i;
};


class TB{
    public:
    TB(){std::cout<<"TB construct"<<std::endl;}
    ~TB(){std::cout<<"TB deconstruct"<<std::endl;}

    TB& TB_Test(){
        std::cout<<"TB Test"<<std::endl;
        return *this;
    }

    void Test(){
        TB & tb = TB_Test();
        std::cout<<"Test"<<std::endl;
    }
};
;
class TC{
    public:
    TC(){std::cout<<"TC construct"<<std::endl;}
    ~TC(){std::cout<<"TC deconstruct"<<std::endl;}

    TB GetTB(){
        return TB{};
    }
};

class TA{
    public:
    TA(){std::cout<<"TA construct"<<std::endl;}
    ~TA(){std::cout<<"TA deconstruct"<<std::endl;}

    TB GetTB(){
        return tc.GetTB();
    }
    TC tc;
};

void Template(){}

template <typename T, typename ... Args>
void Template(T t,Args &... args){
    int size = sizeof ...(args);
    std::cout <<"size:"<<size<<std::endl;
    std::cout<<"t:"<<t<<std::endl;
    Template(std::forward<Args>(args)...);

}

void Test_Template(){}

template<typename T = char, typename ... Args>
void Test_Template(T ch,Args &...args){
    std::cout<<"ch:"<<ch<<std::endl;
    Template<int>(std::forward<Args>(args)...);
}

int main() {

    Temp<OT> temp(1);
    temp.Test();

    TA ta{};
    ta.GetTB().Test(); //test

    Test_Template('a',"Hello");



    return 0;
}