#include <stdio.h>

#include "debug.h"
#include "value.h"

// helper function for printing constant instructions
static int constantInstruction(const char* name, Chunk* chunk, int offset){
    uint8_t constant = chunk -> code[offset+1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]); // print the value from value array 
    printf("'\n");
    //                                                                                    1        2
    return offset + 2; // because 1 index for instructiona nd the 2nd for the value: OP_CONSTANT value
}

// displays information of OP_RETURN type opcodes
static int simpleInstruction(const char* name, int offset){

    printf("%s\n", name);
    return offset + 1;

}

// churns through the instructions in the chunk struct's code array
void disassembleChunk(Chunk* chunk, const char* name){
    printf("== %s ==\n", name);


    for(int offset=0; offset < chunk-> count;){

        offset = disassembleInstruction(chunk, offset); // returns the offset of the next instruction because instructions can have different lengths.


    }
}

// handles the different types of instructions using utility functions
int disassembleInstruction(Chunk* chunk, int offset){

    printf("%04d ", offset);

    if(offset > 0 && chunk -> lines[offset] == chunk->lines[offset-1]){

        printf("   | ");

    }else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instruction = chunk->code[offset];

    switch(instruction){
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }

}

