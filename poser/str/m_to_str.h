//
// Created by tobin on 2024-08-11.
//

#include "to_str.h"

#ifndef POSER_M_TO_STR_H
#define POSER_M_TO_STR_H

#define PRAG_PUSH _Pragma("GCC diagnostic push");                \
    _Pragma("GCC diagnostic ignored \"-Wpointer-to-int-cast\""); \
    _Pragma("GCC diagnostic ignored \"-Wint-to-pointer-cast\""); \
    _Pragma("GCC diagnostic ignored \"-Wpointer-sign\"")         \
    _Pragma("GCC diagnostic ignored \"-Wint-conversion\"")

#define PRAG_POP  _Pragma("GCC diagnostic pop")

//#define PRAG_PUSH
//#define PRAG_POP


typedef struct
{
    char* buf;
    u8 isStack : 1;
} m_to_str_t;

typedef struct
{
    f128 val;
    u8 decimals;
} f_options;

/*It is technically possible to fit this all into 80 lines by breaking the lines
 * but that sounds horrifying to read. This does some fairly clever type
 * fuckery, and in short, converts whatever types you want into heap allocated
 * strings */

/*Wrap the _arg in parenthesis*/
#define to_str(_arg) (to_strv((_arg)))

/*This creates a m_to_str_t struct for each type and "returns" it*/
#define to_strv(_arg)                                                                                                       \
    _Generic((_arg),                                                                                                       \
                                                                                                                           \
    default: ({assertn(false, "Unsupported conversion type. m_to_str.h"); "";}),                                                       \
    char*: ({ m_to_str_t __a = (m_to_str_t){ _arg, 1}; &__a; }),                                                           \
    i64 : ({ PRAG_PUSH; i64 __a = (i64) (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
    i32 : ({ PRAG_PUSH; i32 __a = (i32) (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
    i16 : ({ PRAG_PUSH; i16 __a = (i16) (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
    i8  : ({ PRAG_PUSH; i8 __a  = (i8)  (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
                                                                                                                           \
    u64 : ({ PRAG_PUSH; u64 __a = (u64) (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
    u32 : ({ PRAG_PUSH; u32 __a = (u32) (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
    u16 : ({ PRAG_PUSH; u16 __a = (u16) (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
    u8  : ({ PRAG_PUSH; u8 __a  = (u8)  (_arg); m_to_str_t __ret = (m_to_str_t) {i64_to_sstr(__a), 1}; PRAG_POP; &__ret; }), \
                                                                                                                           \
    m_to_str_t* : ({ PRAG_PUSH; m_to_str_t * __a = (m_to_str_t*) _arg; __a; PRAG_POP; })                                   \
)


#endif //POSER_M_TO_STR_H
