//
// Created by tobin on 2024-09-05.
//

#include "str_cmp.h"

#include "str.h"

i32 str_cmp(const char* a, const char* b) {
    u32 alen = str_len(a);
    u32 blen = str_len(b);

    u32 min = (alen > blen) ? blen : alen;

    u32 i = 0;
    for(; i < min; i++)
    {
        if(a[i] != b[i])
        {
            return a[i] > b[i];
        }
    }

    return 0;
}
