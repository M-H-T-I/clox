#include "common.h"
#include "vm.h"

VM vm;


void initVm(){

}

void freeVm(){

}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk; // both are pointers 
    vm.ip = vm.chunk->code;
    return run();
}

static InterpretResult run(){

    #define READ_BYTE() (*vm.ip++)

    for(;;){
        uint8_t instruction;

        switch (instruction = READ_BYTE())
        {
        case OP_RETURN:
            return INTERPRET_OK;
            break;
        }
    }

    #undef READ_BYTE
}