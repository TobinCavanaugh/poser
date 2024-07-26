//
// Created by tobin on 5/31/2024.
//

#ifndef BOBLIB_BINT_H
#define BOBLIB_BINT_H

//TODO mins & maxes for signed types


typedef __INT8_TYPE__ i8;
#define i8_max __INT8_MAX__
#define i8_min (-(i8_max) - 1)

typedef __UINT8_TYPE__ u8;
#define u8_max ((u8)-1)
#define u8_size sizeof(u8)

typedef __INT16_TYPE__ i16;
#define i16_max __INT16_MAX__
#define i16_min (-(i16_max) - 1)

typedef __UINT16_TYPE__ u16;
#define u16_max ((u16)-1)
#define u16_size sizeof(u16)

typedef __INT32_TYPE__ i32;
#define i32_max __INT32_MAX__
#define i32_min (-(i32_max) - 1)

typedef __UINT32_TYPE__ u32;
#define u32_max ((u32)-1)
#define u32_size sizeof(u32)

typedef __INT64_TYPE__ i64;
#define i64_max __INT64_MAX__
#define i64_min (-(i64_max) - 1)

typedef __UINT64_TYPE__ u64;
#define u64_max ((u64)-1)
#define u64_size sizeof(u64)

typedef u8 byte;
typedef u8 bool;

/* Python style casting functions in the form: i64l(10 + 10)*/

#ifndef LITERAL_FUNCTIONS
#define LITERAL_FUNCTIONS

/* Defines functions for casting to the type python style. */
#define INTERNAL_DEFINE_LITERAL(type) static inline type type ## l (u64 arg) { return (type) arg; }

INTERNAL_DEFINE_LITERAL(i8);
INTERNAL_DEFINE_LITERAL(u8);

INTERNAL_DEFINE_LITERAL(i16);
INTERNAL_DEFINE_LITERAL(u16);

INTERNAL_DEFINE_LITERAL(i32);
INTERNAL_DEFINE_LITERAL(u32);

INTERNAL_DEFINE_LITERAL(i64);
INTERNAL_DEFINE_LITERAL(u64);

#endif

#endif //BOBLIB_BINT_H
