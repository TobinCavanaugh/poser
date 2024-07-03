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
    typedef struct tuple name ## _result ;  \
    name ## _result name

#define var __auto_type
#define VAR __auto_type

/// Performs a convenient conditional return based on the condition. Applies
/// to u0 functions
/// @param condition : The condition to return based on
#define returnif(condition) if(condition){ return; }

/// Performs a convenient conditional return based on the condition. Applies
/// to any function, place the return value in the value argument
/// @param condition : The condition to return based on
/// @param value : The value to return
#define returnif_(condition, value) if(condition){ return value; }

#define INLINE

#endif //POSER_DIALECT_H
