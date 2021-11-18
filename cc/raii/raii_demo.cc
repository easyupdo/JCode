#include <iostream>
#include <functional>
#include <fstream>
#include <mutex>


/*RAII use
1. 创建一个资源包装类
2. 在构造函数中获取资源（可选）
3. 在析构函数中释放资源
4. 在栈上创建资源包装类对象
*/
// like gurad_lock
class scoped_lock
{
public:
    explicit scoped_lock(std::mutex& m)
       : _m(m)
    {
        _m.lock();
    }
    ~scoped_lock(void)
    {
        _m.unlock();
    }
private:
    std::mutex& _m;
};

void eg3(void)
{
    std::mutex m;
    scoped_lock locker(m);
    // 使用资源
}

/*RAII

*/
class RAII{
    public:
    using InitFunc = std::function<void()>;
    using ReleaseFunc = std::function<void()>;
    RAII(const InitFunc &init_func,const ReleaseFunc &relese_func) : _release_func(relese_func) {
        if(init_func) {
            init_func();
        }
    }

    explicit RAII(InitFunc & init_func){

    }

    ~RAII(){
        if(_release_func) {
            _release_func();
        }
    }

    private:
    ReleaseFunc _release_func;
};

class User{
    public:
    explicit User(const std::string&name) : _name(name){
        std::cout<<"name:"<<name<<std::endl;
    }
    User (const std::string&name,const std::string &sex) {
        std::cout<<"name:"<<name<<std::endl;
        std::cout<<"sex:"<<sex<<std::endl;
    }

    std::string&& GetName(){
        std::cout<<"Name:"<<_name<<std::endl;
        return std::move(_name);
    }
    private:
    std::string _name;
}; //RAII

// error code 
enum class UserErrorType: int8_t {
    UserA = 0x01,
    UserB = 0x02,
    UserC = 0x03
};


template<typename T = void>
struct Success{
    Success(){}
};

template <>
struct Success<void>
{

};

template<typename T>
struct Error{
    Error(const T & error_code) : _t(error_code) { // attention const(must)
    }
    T _t;
};

// return class wapper. we use it like error code system
template<typename T>
class Expected{
    public:
    Expected(T &t) : _t(t){}

    Expected(Success<T> &s) : _has_error(false){} 
    Expected(Success<T> &&s) : _has_error(false){}

    Expected(const Success<void> &s) : _has_error(false){} 
    // Expected(Success<void> &&s) : _has_error(false){}


    Expected(Error<T>&e) : _has_error(true),_t(e._t){}
    Expected(Error<T>&&e) : _has_error(true),_t(e._t){}

    ~Expected(){}

    int32_t value(){
        return _t.value();
    }

    private:
    T _t;  //error code
    bool _has_error; //status

};

// class construct wapper
template <typename T>
class AllClass{
    public:
    AllClass(){}

    template<typename...Args>
    void AllClassArgs(Args &...args);

    ~AllClass(){}

    private:

};

template<typename T>
template<typename... Args>
void AllClass<T>::AllClassArgs(Args & ...args) {
    std::cout<<"AllClassArgs Construct"<<std::endl;
    T t(std::forward<Args>(args)...);
};

//main
int main(int argc,char **argv) {
    //RAII wapper
    User *user = nullptr;
    RAII raii([&user]{if(!user){user = new User("FuckYou");}},[&user]{delete user;});//分配在栈上,init_func和release_func保证资源得到初始化和释放。
    std::cout<<user->GetName()<<std::endl;

    // 手动分配空间
    uint8_t tuser[sizeof(User)];

    User * rtuser = nullptr;
    rtuser = new (static_cast<User*>(static_cast<void*>(tuser))) User("SB");


    std::cout<<"tuser:"<<(static_cast<User*>(static_cast<void*>(tuser))->GetName())<<std::endl;

    // multi-class return wapper
    User tu("A");
    Expected<User> error = tu;

    Expected<UserErrorType> error_a = Error<UserErrorType>(UserErrorType::UserA);

    Expected<int> succ = Success<int>();
    Expected<int> succi = Success<>(); // attention template has default value T = void

    //multi-classs construct wapper
    AllClass<User> all_class;
    all_class.AllClassArgs("Jay","Man");

    all_class.AllClassArgs("Jay");


    
    return 0;
}