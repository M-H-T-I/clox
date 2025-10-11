#include <stdio.h>

#include "debug.h"

// churns through the instructions in the chunk struct's code array
void disassembleChunk(Chunk* chunk, const char* name){
    printf("== %s ==\n", name);


    for(int offset=0; offset < chunk-> count;){

        offset = disassembleInstruction(chunk, offset); // returns the offset of the next instruction because instructions can have different lengths.


    }
}

// displays information of OP_RETURN type opcodes
static int simpleInstruction(const char* name, int offset){

    printf("%s\n", name);
    return offset + 1;

}

// handles the different types of instructions using utility functions
int disassembleInstruction(Chunk* chunk, int offset){

    printf("%04d ", offset);

    uint8_t instruction = chunk->code[offset];

    switch(instruction){
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }

}