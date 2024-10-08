//
// Created by tobin on 7/2/2024.
//

#include "str.h"

u64 str_len(char* data) {
    returnif_(data == null, 0)

    int i = 0;
    while (data[i] != 0)
    {
        ++i;
    }

    return i;
}

u64 str_copy(char* dest, char* src) {
    u64 len = str_len(src);
    mem_copy(dest, src, len + 1);
}
