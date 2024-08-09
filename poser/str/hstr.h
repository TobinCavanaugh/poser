//
// Created by tobin on 5/31/2024.
//

#ifndef BOBLIB_hstr_H
#define BOBLIB_hstr_H

#include "../dialect.h"

typedef struct
{
    char* char_arr;
    char* end_ptr;
} hstr_t;

#define HSTR(str) hstr_fromCs(str)

hstr_t* hstr_fromCs(char* source);

u0 hstr_free(hstr_t* str);

u0 hstr_appendCs(hstr_t* base, char* buf);

u0 hstr_append(hstr_t* base, hstr_t* buf);

u0 hstr_appendu64(hstr_t* base, u64 value);

u0 hstr_appendi64(hstr_t* base, i64 value);

u64 internal_C_strlen(char* data);

u0 hstr_set_end(hstr_t* str, u64 len);

u64 hstr_len(hstr_t* str);

#endif //BOBLIB_hstr_H
