#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

// runs a chunk struct 
typedef struct {

    Chunk* chunk;
    
    /* (instruction pointer) keeps track of which intsruction will be excecuted next (program counter)
    (in code array in chunk) */

    uint8_t* ip;

    Value stack[STACK_MAX];
    Value* stackTop

}VM;

typedef enum{

    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR

}InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);


#endif