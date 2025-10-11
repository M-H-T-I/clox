#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// calculates new capacity (handles the case: capacity = 0)
#define GROW_CAPACITY(capacity)  ((capacity) < 8 ? 8: (capacity)*2)

/*If newCount is any other number greater than 0 (almost always the case except with bugs) it reallocs the memory using 
pointer and returns a void* pointer to allow for casting. Also handles the case when no more memory is available. 
*/
#define GROW_ARRAY(type, pointer, oldCount, newCount) (type*)reallocate(pointer, sizeof(type)*oldCount, sizeof(type) * newCount)

// calls reallocate to free up memory by having new size = 0. Returns a null pointer. uses type to pass oldCount parameter to reallocate
#define FREE_ARRAY(type, pointer, oldCount) reallocate(pointer, sizeof(type) * oldCount, 0);

/*use for all dynamic memory management in clox—allocating memory, freeing it, and changing the size of an existing 
allocation. Result depends on newSize. If 0 it frees up memory else it changes the szie of the array using realloc.
*/
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif