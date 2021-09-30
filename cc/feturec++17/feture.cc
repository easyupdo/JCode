#include <iostream>
#include <optional>
#include <variant>
#include <any>

#define pout(x) std::cout<<x<<std::endl;


std::optional<int> Func() {
    return 1;
    // return {};
}


int main(int argc,char**argv) {
    std::optional<int> o_int2{11};
    std::optional<int> o_int{1};
    pout(o_int.value());
    o_int.reset();
    o_int.swap(o_int2);
    pout(o_int.value());

    auto fun = Func();

    if(o_int.has_value()) {
        pout("has value");
        pout(fun.value());
    }else {
        pout("no value");
    }


    std::variant<int,std::string> vc {"Hello"};
    // int i = std::get<int>(vc.index());
    pout(vc.index());
    std::string str = std::get<std::string>(vc);
    pout(str);

    std::any va = {99};
    pout(va.type().name());

    



    return 0;
}