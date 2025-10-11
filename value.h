#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;


typedef struct {

    int count; // stores the address of the next free position to store the value.
    int capacity; // total capacity of the values array
    Value* values; // pointe to memory in the heap representing this array.
    
}ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);


#endif