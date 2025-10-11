#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;


typedef struct {

    int count;
    int capacity;
    Value* values;
}ValueArray;

#endif