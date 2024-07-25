//
// Created by tobin on 7/2/2024.
//

#ifndef POSER_DIALECT_H
#define POSER_DIALECT_H

#include "bint.h"

/// Define a tuple function. Place the tuple within {}. Commas are not allowed
/// because C preprocessor is not particularly clever.
/// @param tuple : The contents of the tuple placed within curly braces. This
/// is defined the same as in structs.
/// @param name : The name of the function. The tuple will be of the type
/// {name}_result.
#define TUPLE_FUNC(tuple, name)             \
    /*@formatter:off : clion directive*/    \
    typedef struct tuple name ## _result ;  \
    name ## _result name
/*@formatter:on*/

// #define var __auto_type

/// Performs a convenient conditional return based on the condition. Applies
/// to u0 functions
/// @param condition : The condition to return based on
#define returnif(condition) if(condition){ return; }

/// Performs a convenient conditional return based on the condition. Applies
/// to any function, place the return value in the value argument
/// @param condition : The condition to return based on
/// @param value : The value to return
#define returnif_(condition, value) if(condition){ return value; }

/// Use u0 as void when its referring to a function returning NOTHING
/// Do NOT use when referring to a void *
typedef void u0;

typedef char chr;

typedef float f32;
#define f32_size sizeof(f32) //4
#define f32_inf (__builtin_inf())
#define f32_nan (__builtin_nanf())

typedef double f64;
#define f64_size sizeof(f64) //8
#define f64_inf (__builtin_inff())
#define f64_nan (__builtin_nan())

typedef long double f128;
#define f128_size sizeof(f128); //16
#define f128_inf (__builtin_infl())


#undef NULL
#define NULL ((void *) 0)
#define null NULL

#define INLINE

#endif //POSER_DIALECT_H
