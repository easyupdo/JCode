#include "context.h"
#include "state.h"

int main(int argc,char**argv) {
    Context *context = new Context();

    StartState start_state;

    context->SetState(&start_state);
    context->DoIt();

    
    return 0;
}