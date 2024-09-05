//
// Created by tobin on 2024-09-05.
//

#include "str_cmp.h"

#include "str.h"

i32 str_cmp(const char* a, const char* b) {
    while (*a == *b++)
        if (*a++ == '\0')
            return (0);
    return (*(u8*)a - *(u8*)(b - 1));
}
