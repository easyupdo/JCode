/*************************************************************************
    > File Name: main.cc
    > Author: JayGuan
    > Mail: 
    > Created Time: Thu 19 Aug 2021 10:55:52 PM PDT
 ************************************************************************/

#include<iostream>
#include<typeinfo>

#include <vector>
#include <type_traits>
#include <map>
#include <functional>
#include <memory>



using namespace std;


#define STD_MSGS_TYPE(x) "std_msgs::msg::"#x

#define _TYPE(x) x

#define k_TYPE(k) #k

#define pout(x) do{std::cout<<x<<std::endl;}while(0);


template<typename T>
void Func(T t){
  std::cout<<"type:"<<typeid(t).name()<<std::endl;
}

void Func_C(std::string type) {
  // _TYPE(type) a;

}



template<typename T>
void DFunc(T arg) {
  std::cout<<"arg templeate:"<<arg<<std::endl;
}



template<>
void DFunc(int arg) {
  std::cout<<"arg int<>:"<<arg<<std::endl;
}


// void DFunc(int arg) {
//   std::cout<<"arg int :"<<arg<<std::endl;
// }

template
void DFunc(int arg);


// template<typename T>
// void DFunc(T arg) {
//   std::cout<<"arg:"<<arg<<std::endl;
// }



template<typename T>
void DArgs(T t){
  std::cout<<"Args End"<<std::endl;
}


template<typename T, typename ... Args>
void DArgs(T arg, Args... args){
  DFunc(arg);
  DArgs(std::forward<Args>(args) ...);
}


template<typename T>
void VecType(T t){
  typename T::value_type a;
  std::cout<<"Type:"<<typeid(a).name()<<std::endl;
}


int IFunc(int i ) {
  return 1;
}

template<typename T>
float FFunc(T t) {
  pout("FFunc");
}
//int 
template<typename T, typename std::enable_if<true, T> :: type* = nullptr>
float SFunc(T t){
  pout(typeid(t).name());
}


typedef struct mem{
  alignas(16) char ca;
  int ia;
}mem;

template<typename Type>
class JVector{
  public:
  JVector(std::initializer_list<Type>lv) {
    v_ = lv;
  }

  Type & operator[](int i){
    return v_[i];
  }

  private:
  std::vector<Type>v_;
};



class RI{
  public:
  RI(){
    pout("RI");
  }

  RI(RI&ri){
    pout("RI&");
  }

  RI(RI&&ri){
    pout("RI&&");
  }

  RI& operator=(RI&ri){
    pout("RI operator");
    this->a = ri.a;
    return *this;
  }

  RI && RInt() {
    return std::move(*this);
  }
  int geta(){return a;}

  int a = 1;
  private:
};


template<typename T>
class MC{
  public:
  // bool operator()(const RI& key1, const RI& key2) {
  //   if (key1.a > key2.a)
  //   return true;
  //   else
  // }
    bool operator()(const T& key1, const T& key2) const
    {
      if(key1.a > key2.a)
      return true;
      else 
      return false;
    }
};


// template<uint64_t ut>
// template<uint32_t ss>
// void UTFunc(){
//   // UT ut;
//   // vector<UT>vut;
//   // pout(typeid(ut));

//   // pout()
// }


template <typename TT>
class Temp2{
  public:
  template<typename UU>
  void Temp2Test(UU u);

};

template<typename TT>
template<typename UU>
void Temp2<TT>::Temp2Test(UU u){
  pout(typeid(UU).name());
}





template <uint64_t UT>
class Temp{
  public:
  void TempTest(){
    std::cout<<"UT:"<<UT<<std::endl;
  }
};

template <uint64_t UT>
void UTest(Temp<UT> ut){
  
}

class OperatorTest11{
  public:
  OperatorTest11(){}
  std::string GetName(){return "Func Jay";}

};

inline OperatorTest11 operator""_jay(const char * name,size_t n) {
  return OperatorTest11();
}

namespace Jay{
class Init{
  public:
  Init(std::string & name,int size){
    this->name = name;
  }

  std::string && GetName() {
    return std::move(this->name);
  }
  private:
  std::string name{""};
};
}//namespace Jay




int main(int argc,char * argv[])
{
  bool st = 10 > 11;
  std::cout<<"st:"<<st<<std::endl;  

  Func(11);
  int a = 100;

  std::cout<<typeid(a).name();

  const int ia = 99;
  const int *const ia_ptr = &ia;

  void * via = reinterpret_cast<void*>(ia);

  std::cout<<"Type:"<<STD_MSGS_TYPE(String)<<std::endl;

  std::string s = "int";
  std::cout<<"_TYPE:"<<k_TYPE("int")<<std::endl;

  _TYPE(int) ta ;

  // stoi("int");

  std::vector<unsigned char> vc = {'a','b','c'};
  std::cout<<"vc:"<<&vc[0]<<std::endl;

  printf("c_vc:%s\n",&vc[0]);

  for(int i = 0;i<5;++i) {

    uint8_t * uint_ptr = &vc[0];

    std::cout<<"uint_ptr:"<<uint_ptr<<std::endl;

  }

  // DArgs("");
  // DArgs(1, 2.5, "test");

  DFunc(1);

  // std::enable_if<>

  std::vector<int>va;
  VecType<std::vector<int>>(va);

  decltype(IFunc(1)) _a;
  pout(typeid(_a).name());
  using TIF = std::function<int()>;

  TIF tif = []() -> int{};

  typedef std::result_of<TIF()>::type TA;


  typedef int(&fn_ref)();
  using FN_REF = std::function<int()>;

  typedef std::result_of<FN_REF()>::type B;         // int




  SFunc(1.1);

  pout(alignof(10));

  pout(sizeof(mem));
  // pout(alignas(1));


  std::cout<<std::is_same<int,int>::value<<std::endl;

  std::initializer_list<int> ili = {1,2,3};
  std::cout<<*ili.begin()<<std::endl;

  JVector<int> jv({1,2,3});
  pout(jv[1]);
  jv[1] = 11;
  pout(jv[1]);


  RI ri;
  RI ri2 = ri;

  RI ri3(ri);

  pout("-----");

  RI &&ri4 = ri.RInt(); 


  // // std::map<Key,T,Compare,Allocator>::map;
  // using mc = std::function<void(const RI& key1, const RI& key2)>;

  // auto map_comp = [](const RI& key1, const RI& key2) -> bool{
  //   return true;
  // };


  pout("new-------");

  map<RI,int,MC<RI>>m;
  // m.insert(std::pair<RI,int>(ri,1));
  m[std::move(ri)] = 1;
  // m[ri] = 1;

  class RH{
    public:
    int test = 1;
    RH(){}
    bool operator< (const RH&rh) const {
      return test < rh.test;
    }
  };

  RH rh;
  map<RH,int> rh_map;
  // rh_map[std::move(rh)] = 111;
  rh_map[rh] = 111;


  int i_ori = 555;
  const int * i_ptr = &i_ori;
  int i2_ori = 666;
  i_ptr = &i2_ori; 

  int * const i3_ptr = &i_ori;
  *i3_ptr = i2_ori;

  // UTFunc<11>();

  Temp<1> temp;

  temp.TempTest();


  Temp2<int> temp2;
  // temp2.Temp2Test<int,int>();

  UTest(temp);


  std::allocator<int> int_allocator;
  int * int_ptr = int_allocator.allocate(1);
  *int_ptr = 10;
  std::cout<<"int_ptr:"<<*int_ptr<<std::endl;
  std::cout<<"max_size:"<<int_allocator.max_size()<<std::endl;

  auto opt_fun = "name"_jay;
  std::cout<<"Name"<<opt_fun.GetName()<<std::endl;

  std::string name = "JayHello";
  Jay::Init in(name,1);
  in.GetName();

  Jay::Init in2 {name,2};
  in2.GetName();
  

return 0;
}

