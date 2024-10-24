//
// Created by tobin on 7/2/2024.
//
#include "comp/bint.h"
#include "comp/bflt.h"

#ifndef POSER_DIALECT_H
#define POSER_DIALECT_H


#define true 1
#define false 0


/// Use u0 as void when its referring to a function returning NOTHING
/// Do NOT use when referring to a void *
//typedef void u0;
#define u0 void

typedef char unsigned chr;

#define POSER_API __attribute__((unused))

POSER_API u8 entry();

#undef NULL
#define NULL ((void *) 0)
#define null NULL

//#define INLINE

#define atomic _Atomic

// CLION FORMATTING : /*@formatter:off*/
// CLION FORMATTING : /*@formatter:on */

/// Performs a convenient conditional return based on the condition. Applies
/// to u0 functions
/// @param condition : The condition to return based on
#define returnif(condition) if(condition){ return; }

/// Performs a convenient conditional return based on the condition. Applies
/// to any function, place the return value in the value argument
/// @param condition : The condition to return based on
/// @param value : The value to return
#define returnif_(condition, value) if(condition){ return value; }

/// Define a tuple function. Place the tuple within {}. Commas are not allowed
/// because C preprocessor is not particularly clever.
/// @param tuple : The contents of the tuple placed within curly braces. This
/// is defined the same as in structs.
/// @param name : The name of the function. The tuple will be of the type
/// {name}_result.
#define TUPLE_FUNC(tuple, name)                                \
    /*@formatter:off : clion directive*/                       \
    typedef struct tuple name ## _result_t ;                   \
    name ## _result_t name /*@formatter:on : clion directive*/

#define INTERNAL_DEFINE_RESULT(type)                                  \
    typedef struct { type value; u8 success; } result_ ## type ## _t;

INTERNAL_DEFINE_RESULT(i8);

INTERNAL_DEFINE_RESULT(i32);

INTERNAL_DEFINE_RESULT(i64);

INTERNAL_DEFINE_RESULT(u8);

INTERNAL_DEFINE_RESULT(u32);

INTERNAL_DEFINE_RESULT(u64);

INTERNAL_DEFINE_RESULT(f32);

INTERNAL_DEFINE_RESULT(f64);

INTERNAL_DEFINE_RESULT(f128);

#endif //POSER_DIALECT_H
