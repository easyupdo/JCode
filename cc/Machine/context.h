#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include "state_base.h"
#include <iostream>

class Context{
    public:
    Context(){
        std::cout<<"Context"<<std::endl;
    }
    ~Context(){}

    void SetState(StateBase * state) {
        this->state = state;
    }


    void DoIt(){
        std::cout<<"Context DoIt"<<std::endl;
        this->state->DoIt();
    }

    private:
    StateBase * state {nullptr};
};

#endif //_CONTEXT_H_