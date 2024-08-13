//
// Created by tobin on 2024-08-11.
//

#include "to_str.h"

#ifndef POSER_M_TO_STR_H
#define POSER_M_TO_STR_H

#define PP _Pragma("GCC diagnostic push"); _Pragma("GCC diagnostic ignored \"-Wpointer-to-int-cast\"")
#define PP_P _Pragma("GCC diagnostic pop")

/*It is technically possible to fit this all into 80 lines by breaking the lines
 * but that sounds horrifying to read. This does some fairly clever type
 * fuckery, and in short, converts whatever types you want into heap allocated
 * strings*/

typedef struct {
    char *buf;
    u8 stack: 1;
} m_to_str_t;

#define to_str(_arg)                                                                                                         \
    _Generic((_arg),                                                                                                         \
    default: ({assertn(false, "Unsupported conversion type"); "";}),                                                         \
                                                                                                                             \
    /*TODO This can be made to use sstr.h... Tho maybe I don't want that. Maybe return a struct indicating whether its stack or heap? dda*/ \
    i64 : ({ PP; i64 __a = (i64) _arg; byte * __data = halloc(19 + 1 + 1); i64_into_buf(__data, (i64) __a) ; __data; PP_P; }),              \
    i32 : ({ PP; i32 __a = (i32) _arg; byte * __data = halloc(10 + 1 + 1); i64_into_buf(__data, (i64) __a) ; __data; PP_P; }),              \
    i16 : ({ PP; i16 __a = (i16) _arg; byte * __data = halloc(6 + 1 + 1);  i64_into_buf(__data, (i64) __a) ; __data; PP_P; }),              \
    i8  : ({ PP; i8 __a  = (i8)  _arg; byte * __data = halloc(3 + 1+ 1);   i64_into_buf(__data, (i64) __a) ; __data; PP_P; }),              \
                                                                                                                                            \
    u64 : ({ PP; u64 __a = (u64) _arg; byte * __data = halloc(20 + 1); u64_into_buf(__data, (u64) __a) ; __data; PP_P; }),   \
    u32 : ({ PP; u32 __a = (u32) _arg; byte * __data = halloc(10 + 1); u64_into_buf(__data, (u64) __a) ; __data; PP_P; }),   \
    u16 : ({ PP; u16 __a = (u16) _arg; byte * __data = halloc(5 + 1);  u64_into_buf(__data, (u64) __a) ; __data; PP_P; }),   \
    u8  : ({ PP; u8 __a  = (u8)  _arg; byte * __data = halloc(3 + 1);  u64_into_buf(__data, (u64) __a) ; __data; PP_P; }),   \
                                                                                                                             \
    char* : ({ PP; char * __a = (char*) _arg; byte * __data = halloc(str_len(__a)  + 1); mem_copy(__data, __a, str_len(__a) + 1); __data; PP_P; }),                                         \
    void* : ({ PP; void * __a = (void*) _arg; assertn(__a == NULL, "Non NULL void pointer cannot be passed to to_str. Please cast to char* or something similar."); "NULL"; PP_P; }),       \
    fstr* : ({ PP; fstr * __a = (fstr*) _arg; u64 __len = fstr_length(__a) ; byte * __data = halloc(__len + 1); mem_copy(__data, __a->data, __len); __data[__len] = '\0'; __data; PP_P; })  \
)

#endif //POSER_M_TO_STR_H
