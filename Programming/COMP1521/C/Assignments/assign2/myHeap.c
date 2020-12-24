// COMP1521 18s1 Assignment 2
// Implementation of heap management system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myHeap.h"

// minimum total space for heap
#define MIN_HEAP  4096
// minimum amount of space for a free Chunk (excludes Header)
#define MIN_CHUNK 32

#define ALLOC     0x55555555
#define FREE      0xAAAAAAAA

typedef unsigned int uint;      // counters, bit-strings, ...

typedef void *Addr;             // addresses

typedef struct {                // headers for Chunks
    uint  status;               // status (ALLOC or FREE)
    uint  size;                 // #bytes, including header
} Header;

static Addr  heapMem;           // space allocated for Heap
static int   heapSize;          // number of bytes in heapMem
static Addr *freeList;          // array of pointers to free chunks
static int   freeElems;         // number of elements in freeList[]
static int   nFree;             // number of free chunks

// Initialise Heap
// Initialises the Heap to one large free chunk
// Sets up the freeList and sets the first value
// Takes parameter size of type int
// Size is the requested number of bytes on the Heap
// Returns 0 on successful setup of Heap
// Returns -1 on failure of Heap setup
int initHeap(int size){
    if(size < MIN_HEAP){
        size = MIN_HEAP;                                    // Set the size to minimum heap size if the requested size is too small
    }
    else if(size % 4 != 0){                                 // Check if size is a multiple of 4
        int mod = size % 4;                                 // Compute size modulo 4
        int add = 4 - mod;                                  // Compute the extra that needs to be added to size to increase size to the next multiple of 4
        size = size + add;                                  // Add the extra to size
    }
    heapSize = size;                                        // Set the heapSize global variable to the appropriate size
    heapMem = malloc(size);                                 // Get a chunk of memory of size to act as the Heap
    if(heapMem == NULL){
        return -1;                                          // If the Heap cannot be established, return -1
    }
    heapMem = memset(heapMem, 0, heapSize);                 // Set the entire Heap to value 0
    Header *chunk = (Header *)(heapMem);                    // Cast the address as a pointer to a Header
    chunk->status = FREE;                                   // Set the status of the Header to Free
    chunk->size = heapSize;                                 // Set the size of the Header to heapSize
    nFree = 1;                                              // We have one free chunk on the Heap - set global variable nFree = 1
    freeElems = size/MIN_CHUNK;                             // Set the maximum number of free chunks possible on the Heap
    uint freeListBytes = freeElems*sizeof(Addr);            // Set the size of the freeList array for mallocing
    freeList = malloc(freeListBytes);                       // Set up some memory for the freeList 
    if(freeList == NULL){
        return -1;                                          // If the freeList cannot be established, return -1
    }
    freeList = memset(freeList, 0, freeListBytes);          // Set all values in the freeList initially to 0
    freeList[0] = heapMem;                                  // One free chunk exists on the Heao, hence freeList[0] holds a pointer to the start of the Heap

    return 0;                                               // Return 0 on success
}

// Clean Heap
// Frees the mallocd space for the Heap and the freeList
// Takes no parameters
// Returns nothing
void freeHeap(){
    free(heapMem);
    free(freeList);
}

// Allocate a Chunk of Memory
// Finds the optimal free chunk for the user's request
// Updates the Heap and the freeList when chunk is allocated
// Takes parameter size of type int
// Size is the requested number of bytes of memory
// Returns a pointer to the start of the memory chunk when successful
// Returns NULL on failure to find a valid free chunk
void *myMalloc(int size){
    if(size < 1){
        return NULL;                                                                // If the size of the requested malloc is less than 1 byte, return NULL
    }
    else if(size % 4 != 0){                                                         // Check if size is a multiple of 4 
        int mod = size % 4;                                                         // Compute size modulo 4
        int add = 4 - mod;                                                          // Compute the extra that needs to be added to size to increase size to the next multiple of 4
        size = size + add;                                                          // Add the extra to size
    }
    Header *chunkM = (Header *)(freeList[0]);                                       // Cast the address as a pointer to a Header
    uint maxSize = chunkM->size;                                                    // Set the maxSize variable to the size of the first free chunk
    for(int i = 0; i < nFree; i++){
        chunkM = (Header *)(freeList[i]);                                           // Update chunkM to be pointing to the next free chunk's Header
        if(chunkM->size > maxSize){                                                 // If its size is greater than the previous free chunk's size, update the maxSize variable
            maxSize = chunkM->size;
        }
    }

    Header *chunk = (Header *)(freeList[0]);                                        // Cast the address as a pointer to a Header
    int position = 0;                                                               // Set the position of the optimal free chunk to be at position 0 in the freeList
    Header *freeChunk = NULL;                                                       // Set the pointer to the Header of the optimal free chunk to be NULL
    for(int i = 0; i < nFree; i++){
        chunk = (Header *)(freeList[i]);                                            // Update chunk to be pointing to the next free chunk's Header
        if(chunk->size <= maxSize && chunk->size >= size + sizeof(Header)){         // If chunk's size is less than the previous free chunk's size, and has the requested size + Header size
            position = i;                                                           // Update the holder variables to hold the new most optimal chunk
            maxSize = chunk->size;
            freeChunk = chunk;
        }
    }
    if(freeChunk == NULL){
        return NULL;                                                                // If the pointer to the Header of the optimal free chunk is NULL, return NUll
    }

    uint benchmark = size + sizeof(Header) + MIN_CHUNK;                             // Set up the benchmark variable to make checking what type of allocation will be performed easier
    Addr p = (Addr)((char *)freeList[position] + sizeof(Header));                   // Calculate the address to be returned to the requestor for their memory space on the Heap
    if(freeChunk->size < benchmark){                                                // If the free chunk's size is less than the benchmark, allocate the entire chunk to the requestor
        freeChunk->status = ALLOC;                                                  // Set the status of the Header to ALLOC
        freeList[position] = 0;                                                     // Remove the freeList entry for that chunk, as it is no longer free
        for(int j = position; j < nFree-1; j++){
            freeList[j] = freeList[j+1];                                            // Shuffle all remaining entries in the freeList to fill the gap created
        }
        nFree--;                                                                    // Decrement the counter of free chunks
    }
    else{                                                                           // Else, split the free chunk into an allocated chunk and a remaining free chunk
        uint initSize = freeChunk->size;
        freeChunk->status = ALLOC;                                                  // Set the status of the Header to ALLOC
        freeChunk->size = size + sizeof(Header);                                    // Update the size of the free chunk to be the requested size + Header size
        Addr newFreeA = (Addr)((char *)freeList[position] + freeChunk->size);       // Calculate the address of the new free chunk created from the excess
        Header *insert = (Header *)newFreeA;                                        // Cast the address as a pointer to a Header
        insert->status = FREE;                                                      // Set its status to FREE
        insert->size = initSize - freeChunk->size;                                  // Set the size to the leftover bytes from the allocated chunk
        freeList[position] = newFreeA;                                              // Update the memory address that the freeList entry used to point to
    }

    return p;                                                                       // Return the address to the requestor of where their memory region begins (excludes Header)
}

// Free a Chunk of Memory
// Finds the chunk the user is requesting to free
// Resets the values stored and changes status to FREE
// Updates the freeList
// Merges any adjacent free chunks to prevent fragmentation
// Takes parameter block of type void *
// Block is a pointer to a memory block that the user wants freed
// Returns nothing on success
// Prints error message and exits with code 1 on failure
void myFree(void *block){
    if(block == NULL){                                                              // If the pointer provided for the block to be freed is NULL, print err msg and exit
        printf("Attempt to free unallocated chunk\n");
        exit(1);
    }   
    Addr headA = (Addr)((char *)block - sizeof(Header));                            // Find the Header address for the chunk the requestor wants to free, which is Header size back from block
    Header *check = (Header *)headA;                                                // Cast the address as a pointer to a Header
    if(check->status != ALLOC){                                                     // Check if the requested chunk to be freed is actually allocated
        printf("Attempt to free unallocated chunk\n");                              // If it does not have the value ALLOC, print err msg and exit
        exit(1);
    }   
    check->status = FREE;                                                           // If all the previous checks have been passed, then set the status of the chunk's Header to FREE
    Addr memSetAd = (Addr)((char *)headA + sizeof(Header));                         // Calculate the address of where the memory section of the chunk began 
    memSetAd = memset(memSetAd, 0, check->size - sizeof(Header));                   // Reset all values back to 0

    int insertP = -1;                                                               // Set up a variable that will be used to store the position of where the new free list entry will be inserted
    for(int i = 0; i < nFree; i++){
        if(freeList[i] > headA){                                                    // Find the first address in freeList that is greater than the address of the newly freed chunk
            insertP = i;                                                            // Store the index of this address
            break;                                                                  // Break the loop, as we only need to find the first time that this occurs
        }
    }
    if(insertP == -1){                                                              // If the insert position hasn't been changed since initialisation
        insertP = nFree;                                                            // Insert the address of the newly freed chunk in the next open position in freeList
        freeList[insertP] = headA;
        nFree++;                                                                    // Increase the counter for how many free chunks exist on the Heap
    }
    else{
        for(int j = nFree-1; j >= insertP; j--){                                    // Else, shuffle all values in the freeList from the insert position up by one
            freeList[j+1] = freeList[j];
        }
        freeList[insertP] = headA;                                                  // Insert the address of the newly freed chunk to the space made in the freeList
        nFree++;                                                                    // Increase the counter for how many free chunks exist on the Heap
    }

    if(insertP <= nFree-2){                                                         // Check if where the free chunk was placed in the freeList was to the left of the last position
        Header *above = (Header *)(freeList[insertP+1]);                            // Compute the address of the next free chunk above the newly freed chunk
        Addr aboveAS = (Addr)((char *)freeList[insertP] + check->size);             // Compute the address of the next chunk above the newly freed chunk
        if(aboveAS == freeList[insertP+1]){                                         // Check if the address of the next chunk above the newly freed chunk is a free chunk
            check->size += above->size;                                             // If so, merge the two chunks into the lower chunk. Update size first to be the size of the two chunks
            memset(freeList[insertP+1], 0, sizeof(Header));                         // Remove the header of the upper chunk, by setting all values to 0 over it
            for(int i = insertP+1; i < nFree-1; i++){
                freeList[i] = freeList[i+1];                                        // Shuffle down the freeList, as we have merged the right chunk into the newly freed chunk
            }
            nFree--;                                                                // Decrease the counter for how many free chunks exist on the Heap
        }
    }

    if(insertP >= 1){                                                               // Check if where the free chunk was placed in the freeList was to the right of the first position
        Header *below = (Header *)(freeList[insertP-1]);                            // Compute the address of the free chunk below the newly freed chunk
        Addr belowAS = (Addr)((char*)freeList[insertP-1] + below->size);            // Compute the address of the next chunk above the below free chunk
        if(belowAS == freeList[insertP]){                                           // Check if the adress of the next chunk above the below free chunk is the address of the newly freed chunk
            below->size += check->size;                                             // If so, merge the newly freed chunk into the free chunk below. Update size of below free chunk
            memset(freeList[insertP], 0, sizeof(Header));                           // Remove the header of the newly freed chunk, by setting all values to 0 over it
            for(int j = insertP; j < nFree-1; j++){
                freeList[j] = freeList[j+1];                                        // Shuffle down the freeList, as we have merged the newly freed chunk into the free chunk to its left
            }
            nFree--;                                                                // Decrease the counter for how many free chunks exist on the Heap
        }
    }
}

// Convert Pointer to Offset in Heap
// Converts a pointer to a memory region to an offset into the Heap
// Takes parameter p of tyoe void *
// P is a memory address
// Returns an offet of type int on success
// Returns -1 on failure
int  heapOffset(void *p){
    Addr heapTop = (Addr)((char *)heapMem + heapSize);
    if (p == NULL || p < heapMem || p >= heapTop)
        return -1;
    else
        return p - heapMem;
}

// Dump Contents of Heap
// Dumps the current Heap and prints its information to the terminal
// Takes no parameters
// Returns nothing on success
// Prints error message and exits with code 1 on failure
void dumpHeap(){
    Addr    curr;
    Header *chunk;
    Addr    endHeap = (Addr)((char *)heapMem + heapSize);
    int     onRow = 0;

    curr = heapMem;
    while (curr < endHeap) {
        char stat;
        chunk = (Header *)curr;
        switch (chunk->status) {
        case FREE:  stat = 'F'; break;
        case ALLOC: stat = 'A'; break;
        default:    fprintf(stderr,"Corrupted heap %08x\n",chunk->status); exit(1); break;
        }
        printf("+%05d (%c,%5d) ", heapOffset(curr), stat, chunk->size);
        onRow++;
        if (onRow%5 == 0) printf("\n");
        curr = (Addr)((char *)curr + chunk->size);
    }
    if (onRow > 0) printf("\n");
}
