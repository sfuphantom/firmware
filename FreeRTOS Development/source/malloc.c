/*
 * malloc.c
 *
 *  Created on: Jun 7, 2018
 *      Author: sormoh
 */

#include<stdio.h>
#include<stddef.h>
#include "malloc.h"
#include "sci.h"

/* Initialize the first metadata block */
void initialize(){
    freeList->size = 20000 - sizeof(struct block); //The size of the block
    freeList->free = 1; //The block is not yet allocated
    freeList->next = NULL; //The first metadata has no next metadata block yet
}

/* Split function for a new block allocation by splitting a free block
 *     struct block *fitting_slot: pointer to the metadata block which refers to the block of memory whose
 *                                 size is more than required
 *     size: the required size of the memory chunk to be allocated
 *
 * */
void split(struct block *fitting_slot, size_t size){
    struct block *new = (void*)((void*)fitting_slot + size + sizeof(struct block));

    new->size = (fitting_slot->size - size - sizeof(struct block));
    new->free = 1;
    new->next = fitting_slot->next;
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;

}


void *MyMalloc(size_t noOfBytes){
    struct block *curr, *prev;
    void *result;

    // Will be executed if the size of the first metadata block is not set yet
    if (!(freeList->size)){
        initialize();
        sciSend(scilinREG,20,(unsigned char*)"Memory Initialized \r\n");
       }

    curr = freeList;

    // If this condition is met, the metadata block we checked cannot be used for the allocation.
    // So we execute the following statements. That is you go on checking one metadata block at a time.
    while( ((curr->size)<noOfBytes) || ((curr->free)==0) && (curr->next!=NULL) ){
        prev = curr;
        curr = curr->next;
        sciSend(scilinREG,20,(unsigned char*)"One block checked\r\n");

    }

    // If this condition is met, the metadata block we checked refers to a chunk of memory that exactly fits the required size.
    // So set the free flag to 0, indicating that it is allocated. Then return the starting address of the block of allocated memory.
    if( (curr->size)==noOfBytes ){
        curr->free = 0;
        result=(void*)(++curr);
        sciSend(scilinREG,30,(unsigned char*)"Exact fitting block allocated\r\n");
        return result;

    } else if((curr->size)>(noOfBytes+sizeof(struct block))){

        split(curr,noOfBytes);
        result = (void*)(++curr);
        sciSend(scilinREG,40,(unsigned char*)"Fitting block allocated with a split\r\n");
        return result;
    } else {
        result=NULL;
        sciSend(scilinREG,40,(unsigned char*)"Sorry. No sufficient memory to allocate\r\n");
        return result;
    }


}

/*
 * This is to merge the consecutive free blocks by removing the metadata block in the middle. This will save space.
*/

void merge(){
    struct block *curr,*prev;
    curr=freeList;
    while((curr->next)!=NULL){
        if((curr->free) && (curr->next->free)){
            curr->size+=(curr->next->size)+sizeof(struct block);
            curr->next=curr->next->next;
           }
    prev=curr;
    curr=curr->next;
 }
}

void MyFree(void* ptr){
    // Here we check whether the address to which the pointer given as an argument
    // to the function actually lies within the address range of the memory array that we used for the purpose
    if(((void*)memory<=ptr)&&(ptr<=(void*)(memory+20000))){
        struct block* curr=ptr;
        --curr;
        curr->free=1;
        merge();
     } else
         sciSend(scilinREG,40,(unsigned char*)"Please provide a valid pointer allocated by MyMalloc\r\n");
     }

