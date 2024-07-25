//
// Created by tobin on 5/31/2024.
//

#ifndef BOBLIB_BINT_H
#define BOBLIB_BINT_H

//TODO mins & maxes for signed types

typedef signed char i8;
typedef unsigned char u8;
#define u8_max ((u8)-1)
#define u8_size sizeof(u8)

typedef short i16;
typedef unsigned short u16;
#define u16_max ((u16)-1)
#define u16_size sizeof(u16)

typedef int i32;
typedef unsigned u32;
#define u32_max ((u32)-1)
#define u32_size sizeof(u32)

typedef long long i64;
typedef unsigned long long u64;
#define u64_max ((u64)-1)
#define u64_size sizeof(u64)

typedef u8 byte;
typedef u8 bool;

#endif //BOBLIB_BINT_H
