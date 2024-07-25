//
// Created by tobin on 5/31/2024.
//

#ifndef BOBLIB_BINT_H
#define BOBLIB_BINT_H
#include "dialect.h"

//TODO include maxes for shit, maybe grab cnum.h


typedef signed char i8;
typedef unsigned char u8;
#define u8_max (u8)-1
#define u8_size sizeof(u8) //1

typedef short i16;
typedef unsigned short u16;
#define u16_max (u16)-1
#define u16_size sizeof(u16) //2

typedef int i32;
typedef unsigned u32;
#define u32_max (u32)-1
#define u32_size sizeof(u32) //4

typedef long long i64;
typedef unsigned long long u64;
#define u64_max (u64)-1
#define u64_size sizeof(u64) //8


typedef u8 byte;
typedef u8 bool;
#define true 1
#define false 0

#define RESULT_DEFINITION(type) typedef struct { u8 success; type value; } result_ ## type;

RESULT_DEFINITION(i8);
RESULT_DEFINITION(i32);
RESULT_DEFINITION(i64);

RESULT_DEFINITION(u8);
RESULT_DEFINITION(u32);
RESULT_DEFINITION(u64);

RESULT_DEFINITION(f32);
RESULT_DEFINITION(f64);
RESULT_DEFINITION(f128);


#endif //BOBLIB_BINT_H
