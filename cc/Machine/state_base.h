#ifndef _STATE_BASE_H_
#define _STATE_BASE_H_
#include <iostream>
class StateBase{
    public:
    StateBase(){
        std::cout<<"StateBase"<<std::endl;
    }
    ~StateBase(){}

    virtual void DoIt(){
        std::cout<<"StateBase DoIt"<<std::endl;
    }

};

#endif //_STATE_BASE_H_