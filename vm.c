#include "common.h"
#include "vm.h"
#include <stdio.h>
#include "debug.h"

VM vm;

static void resetStack(){
    vm.stackTop = vm.stack;
}


void initVM(){

    resetStack();

}

void push(Value value){

    *vm.stackTop = value;
    vm.stackTop++;

}

Value pop(){
    vm.stackTop--;
    return *vm.stackTop;
}

void freeVM(){

}

static InterpretResult run(){

    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    #ifdef DEBUG_TRACE_EXECUTION

        printf("            ");
        for(Value* slot = vm.stack;slot < vm.stackTop; slot++){
            printf("[ ");
            printValue(*slot);
            printf("]");
        }

        printf("\n");



        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code)); // ip is absolute pointer so we convert it to relative index using arithmetic 

    #endif

    for(;;){
        uint8_t instruction;

        switch (instruction = READ_BYTE()){

            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                printValue(constant);
                printf("\n");
                break;
            }
        
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
                break;
            }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    
}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk; // both are pointers 
    vm.ip = vm.chunk->code;
    return run();
}

