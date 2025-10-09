#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// calculates new capacity (handles the case: capacity = 0)
#define GROW_CAPACITY(capacity)  ((capacity) < 8 ? 8: (capacity)*2)

// calls reallocate
#define GROW_ARRAY(type, pointer, oldCount, newCount) (type*)reallocate(pointer, sizeof(type)*oldCount, sizeof(type) * newCount)

//use for all dynamic memory management in clox—allocating memory, freeing it, and changing the size of an existing allocation.
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif