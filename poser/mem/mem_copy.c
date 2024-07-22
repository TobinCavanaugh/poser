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

#define MEM_COPY_INSTRUCTION_DEBUG 0

#if MEM_COPY_INSTRUCTION_DEBUG

#include "../osio/osio.h"

#endif

inline void print_instruction_debug_message(char* message) {
#if MEM_COPY_INSTRUCTION_DEBUG
    io_printCs(message);
#endif
}


//We need this to make pasting the type and the comma together easier
#define PASTE_SEQ(seq) #seq

//Horrifying macro for generating a casting for loop for a sized type.
#define MEM_COPY_FOR(dest, source, offset, len, type)                       \
for(; len >= sizeof(type); len -= sizeof(type)) {                           \
    /*
    Debug printing function, this should get entirely optimized out when
    MEMCOPY_INSTRUCTION_DEBUG is 0
    */                                                                      \
    print_instruction_debug_message(PASTE_SEQ(type) ",");                   \
                                                                            \
    /*We do a cast of both sides to */                                      \
    *((type*) (dest + offset)) = *((type *) (source + offset));             \
    offset += sizeof(type);                                                 \
}

u0 mem_copy(void* destination, void* source, i64 len) {
    typedef struct
    {
        u64 _a, _b, _c, _d;
    } block32B;

    typedef struct
    {
        block32B _a, _b, _c, _d;
    } block128B;

    typedef struct
    {
        block128B _a, _b;
    } block256B;

    typedef struct
    {
        block256B _a, _b;
    } block512B;

    typedef struct
    {
        block256B _a, _b, _c, _d;
    } block1024B;

    int offset = 0;

    // MEM_COPY_FOR(destination, source, offset, len, block1024B);
    // MEM_COPY_FOR(destination, source, offset, len, block512B);
    // MEM_COPY_FOR(destination, source, offset, len, block256B);
    // MEM_COPY_FOR(destination, source, offset, len, block128B);
    // MEM_COPY_FOR(destination, source, offset, len, block32B);
    // MEM_COPY_FOR(destination, source, offset, len, u64);
    // MEM_COPY_FOR(destination, source, offset, len, u8);
    // while (len >= 0)
    // {
    // *(u8*)destination++ = *(u8*)source++;
    // len--;
    // }


    char* d = destination;
    const char* s = source;
    while (len--)
    {
        *d++ = *s++;
    }

    // __builtin_memcpy(destination, source, len);

    // i64 ll = len;

    // u64 _tmp = 10;
    // for(; _tmp > 1; _tmp--)
    // {
    // ll -= 1;
    // hstr * tmp = i64_to_hstr(ll);
    // put_hsn(tmp);
    // hstr_free(tmp);
    // }
}
