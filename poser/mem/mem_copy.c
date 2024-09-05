//
// Created by tobin on 6/3/2024.
//

///
/* NOTES:
 * PERFORMANCE ===============================================================
 * 2024/06/03| we are operating at ~9920us for 100k iterations of 1800B
 * copying, this is ~2.5 times slower than native malloc implementation.
 *
 * SIMD ======================================================================
 * SIMD intrinsics don't seem to provide any significant performance, at least
 * during my testing with SSE on my Ryzen 7 2700x. I'll need to check on
 * laptop to see if AVX512F has a significant improvement, however I kinda
 * doubt it, and I assume this code is just loading this stuff into L1 cache
 * anyways, and the overhead of loading into registers is slower than L1. This
 * was the case even when unrolling the loops up to 128B.
 *
 * Casting ===================================================================
 * Interpreting the data array as a block and operating on that array is MUCH
 * slower than doing inline casting. Doesn't make sense to me but thems the
 * brakes.
 *
 * Memcpy ====================================================================
 * Theres a thing called __builtin_memcpy where it just uses the compilers
 * implementation of memcpy. While this is faster, I'd count that as using the
 * libC implementation, so as such it will not be used here.
 *
 */


#include "mem_copy.h"

#include "../io/put.h"

#define MEM_COPY_BUGGY 0
#define MEM_COPY_INSTRUCTION_DEBUG 0

#if MEM_COPY_INSTRUCTION_DEBUG
#include "../io/put.h"
#endif

inline void print_instruction_debug_message(char *message) {
#if MEM_COPY_INSTRUCTION_DEBUG
    put_sn(message);
#endif
}


//We need this to make pasting the type and the comma together easier
#define assert_PASTE_SEQ(seq) #seq

//Horrifying macro for generating a casting for loop for a sized type.
#define INTERNAL_MEM_COPY_FOR(dest, source, offset, len, type)              \
for(; len >= sizeof(type); len -= sizeof(type)) {                           \
    /*
    Debug printing function, this should get entirely optimized out when
    MEMCOPY_INSTRUCTION_DEBUG is 0
    */                                                                      \
    print_instruction_debug_message(assert_PASTE_SEQ(type) ",");                   \
                                                                            \
    /*We do a cast of both sides to */                                      \
    *((type*) (dest + offset)) = *((type *) (source + offset));             \
    offset += sizeof(type);                                                 \
}

u0 mem_copy(const void *destination, const void *source, i64 len) {
    //Use stupid brain implementation if the MEM_COPY_BUGGY macro is not 0
#if MEM_COPY_BUGGY
    u8* d = destination;
    u8* s = source;
    while (len--)
    {
        *d++ = *s++;
    }
    //Use the cool dude implementation if the MEM_COPY_BUGGY macro is 0
#else
    typedef struct {
        u64 _a, _b, _c, _d;
    } mem_copy_block32B_t;

    typedef struct {
        mem_copy_block32B_t _a, _b, _c, _d;
    } mem_copy_block128B_t;

    typedef struct {
        mem_copy_block128B_t _a, _b;
    } mem_copy_block256B_t;

    typedef struct {
        mem_copy_block256B_t _a, _b;
    } mem_copy_block512B_t;

    typedef struct //1KB
    {
        mem_copy_block256B_t _a, _b, _c, _d;
    } mem_copy_block1024B_t;
    //TODO look into >= MB copying structs... not sure if with it


    int offset = 0;

    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, mem_copy_block1024B_t);
    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, mem_copy_block512B_t);
    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, mem_copy_block256B_t);
    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, mem_copy_block128B_t);
    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, mem_copy_block32B_t);
    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, u64);
    INTERNAL_MEM_COPY_FOR(destination, source, offset, len, u8);
#endif
}
