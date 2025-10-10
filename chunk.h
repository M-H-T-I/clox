//module to define our code representation

#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

// all possible bytecode instructions like the ones in assembly
typedef enum{
    OP_RETURN, // return value from current function
} OpCode; 


// represents a block of compiled bytecode (a function, method, block, script, etc.)
typedef struct {

    int count; // count of elements in use
    int capacity; // count of elements in array

    // a pointer to a bytecode opcode
    uint8_t* code;

}Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void freeChunk(Chunk* chunk);

#endif 