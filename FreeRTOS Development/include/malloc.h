/*
 * malloc.h
 *
 *  Created on: Jun 7, 2018
 *      Author: sormoh
 */

#ifndef INCLUDE_MALLOC_H_
#define INCLUDE_MALLOC_H_


// Declaration of the array which is considered as memory
char memory[20000];

// This structure contains metadata of each block allocated or deallocated
struct block {
    size_t size; // size of the block described by it
    int free; // Is the block described by the metadata free or not?
    struct block *next; // Points to the next metadata block
};

// Initialize a pointer of type "block", named freeList pointing to the
// starting address of the chunk memory we created before
struct block *freeList = (void*) memory;

void initialize();
void split(struct block *fitting_slot,size_t size);
void *MyMalloc(size_t noOfBytes);
void merge();
void MyFree(void* ptr);

#endif /* INCLUDE_MALLOC_H_ */
