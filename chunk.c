#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

// initialze a chunk structure
void initChunk(Chunk* chunk){
    chunk -> count = 0;
    chunk -> capacity = 0;
    chunk -> code= NULL;
    chunk -> lines = NULL;
    initValueArray(& (chunk -> constants));
}

// writes a new byte to the Chunk data structure
void writeChunk(Chunk* chunk, uint8_t byte, int line){
    if(chunk -> capacity < chunk -> count +1){
        int oldCapacity = chunk->capacity;
        chunk -> capacity = GROW_CAPACITY(oldCapacity);
        chunk -> code = GROW_ARRAY(uint8_t, (chunk -> code), (oldCapacity), (chunk -> capacity));
        chunk -> lines = GROW_ARRAY(int, chunk -> lines, oldCapacity, chunk -> capacity);
    }

    chunk -> code[chunk->count] = byte;
    chunk -> lines[chunk->count] = line;
    chunk -> count++;
}

// deallocates memory 
void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t, chunk -> code, chunk -> capacity);
    FREE_ARRAY(int, chunk -> lines, chunk -> capacity)
    freeValueArray(&(chunk -> constants));
    initChunk(chunk);
}

// stores the value of the constant in the value array and returns the index of where in that array it was stored. THe index is stored in t he code array
int addConstant(Chunk* chunk, Value value){

    writeValueArray(&chunk->constants, value);
    return chunk->constants.count-1; // the index where value was stored

}
