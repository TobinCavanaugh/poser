//
// Created by tobin on 2024-08-10.
//

#include "mem_cmp.h"

//TODO Stolen from https://github.com/gcc-mirror/gcc/blob/master/libiberty/memcmp.c
i8 mem_cmp(const void *a, const void *b, const u64 size) {
    register const unsigned char *s1 = (const unsigned char *) a;
    register const unsigned char *s2 = (const unsigned char *) b;

    u64 isize = size;

    while (isize-- > 0) {
        if (*s1++ != *s2++)
            return s1[-1] < s2[-1] ? -1 : 1;
    }

    return 0;
}