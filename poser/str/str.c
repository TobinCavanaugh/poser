//
// Created by tobin on 7/2/2024.
//

#include "str.h"

u64 str_len(char* data) {
    int i = 0;
    while (data[i] != 0)
    {
        ++i;
    }

    return i;
}
