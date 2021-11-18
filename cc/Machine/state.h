#ifndef _STATE_H_
#define _STATE_H_
#include "state_base.h"
#include <iostream>
// union state
// {
//     /* data */
//     START,

// };

enum class state : int8_t{
    START = 1,
    RUNNING = 2,
    STOP = 3
};



class StartState : public StateBase{
    public:
    StartState(){
        std::cout<<"StartState"<<std::endl;
    }
    ~StartState(){}
    virtual void DoIt(){
        std::cout<<"StartState DoIt"<<std::endl;
    }
};

class RunningState{
    public:
    RunningState(){
        std::cout<<"RunningState"<<std::endl;
    }
};

class StopState{
    public:
    StopState(){
        std::cout<<"StopState"<<std::endl;
    }
};


#endif //_STATE_H_