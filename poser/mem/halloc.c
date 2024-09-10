//
// Created by tobin on 5/31/2024.
//

#include "halloc.h"

#include "mem_copy.h"
#include "../comp/assert.h"

#if SYS_OS == OS_WIN

#include <memoryapi.h>

#else
#include <unistd.h>
#include <sys/syscall.h>
#endif

#if HALLOC_USE_CANARY

//Our canary, it can be any data
#define canary 0x0A

//Macro for finding the canary of the block
#define GET_BLOCK_CANARY(newBlock) ((typeof(canary) *) ((u8 *) newBlock + sizeof(heap_block_t) + newBlock->size))

#else

#define canary 0

#endif

/// This datastructure handles our freed heap blocks
typedef struct heap_block_t {
    struct heap_block_t *next;
    u64 size;
    u8 freed;
} heap_block_t;

/// The start of our heap blocks
static heap_block_t heap_head = {0};

/// The alignment of our memory, this aligns to 16B boundaries
static const u64 alignment = 16;

/// The amount of data allocated on the heap
static u64 total_heap_allocation = 0;


/// The boblib counterpart to halloc. Performs a heap allocation.
/// Use hfree to free memory allocated by this
__attribute__((malloc))
byte *halloc(u64 size) {
#ifdef MEM_HEAP_USE_CANARY
    //Add some extra size for the canary
    size += sizeof(canary);
#endif

    //Round size to the nearest power of two, only works if alignment is a pow of two
    //https://stackoverflow.com/a/5422447/21769995
    size = (size + u64_size + (alignment - 1)) & ~(alignment - 1);

    heap_block_t *next = heap_head.next;
    heap_block_t *last = &heap_head;

    //Try and find an open block
    while (next != null) {
        if (next->freed && next->size >= (size - sizeof(canary))) {
            //Use this memory
            next->freed = false;
            return ((u8 *) next) + sizeof(heap_block_t);
        }

        if (next != null) {
            last = next;
        }
        next = next->next;
    }

    //No open blocks
    heap_block_t *newBlock;

    //TODO This is not ideal afaik
#if SYSTEM_OS == OS_WIN
    newBlock = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#elif
    newBlock = (heap_block_t*) sbrk(size);
#endif

    if (newBlock == NULL) {
        return NULL;
    }

    newBlock->size = size;
    newBlock->freed = false;

    last->next = newBlock;

    total_heap_allocation += newBlock->size;

#if HALLOC_USE_CANARY
    *GET_BLOCK_CANARY(newBlock) = canary;
#endif

    return ((u8 *) newBlock) + sizeof(heap_block_t);
}

heap_block_t *find_block_of_ptr(void *ptr) {
    heap_block_t *next = &heap_head;
    while (1) {
        //If our pointer is within that heap block
        if ((u64) next <= (u64) ptr && (u64) next + sizeof(heap_block_t) + next->size >= (u64) ptr) {
            return next;
        }

        if (next->next == NULL) {
            return NULL;
        }

        next = next->next;
    }
}

/// Frees memory allocated on the heap by mem_halloc()
/// @param ptr The pointer to the data of the block to be freed.
u0 hfree(void *ptr) {
    heap_block_t *block = find_block_of_ptr(ptr);

    if (block != NULL) {
        block->freed = true;
        //        memset((u8 *) block + sizeof(heap_block_t), '-', block->size);

#if HALLOC_USE_CANARY
        assertn(*GET_BLOCK_CANARY(block) == canary, "Canary overwritten. This indicates a buffer overflow");
#endif

        //Prevent wrap around
        if (total_heap_allocation - block->size >= total_heap_allocation) {
            total_heap_allocation = 0;
        } else {
            total_heap_allocation -= block->size;
        }
    }
}

/// Reallocates the heap block at ptr to a new block of size.
/// @param ptr The pointer to the heap block data
/// @param size The size of the reallocation
/// @return Returning NULL is the failure state, where no state changes
byte *hrealloc(void *ptr, u64 size) {
    void *new = halloc(size);
    if (new == NULL) {
        return NULL;
    }

    heap_block_t *current = find_block_of_ptr(ptr);

    assert(current != NULL);

    mem_copy(new, ptr, current->size);

    hfree(ptr);

    return new;
}

/// Get the current amount of heap allocated bytes
/// @return The amount of bytes
u64 mem_get_total_heap_alloc() {
    return total_heap_allocation;
}
