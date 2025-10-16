#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

// runs a chunk struct 
typedef struct {

    Chunk* chunk;

}VM;

void initVM();
void freeVM();


#endif