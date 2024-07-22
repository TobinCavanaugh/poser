//
// Created by tobin on 5/31/2024.
//

#ifndef BOBLIB_hstr_H
#define BOBLIB_hstr_H

#include "../comp/bint.h"

typedef struct
{
    char* char_arr;
    char* end_ptr;
} hstr;

#define HSTR(str) hstr_fromCs(str)

hstr* hstr_fromCs(char* source);

u0 hstr_free(hstr* str);

u0 hstr_appendCs(hstr* base, char* buf);

u0 hstr_append(hstr* base, hstr* buf);

u0 hstr_appendu64(hstr* base, u64 value);

u0 hstr_appendi64(hstr* base, i64 value);

u64 internal_C_strlen(char* data);

u0 hstr_set_end(hstr* str, u64 len);

u64 hstr_len(hstr* str);

#endif //BOBLIB_hstr_H
