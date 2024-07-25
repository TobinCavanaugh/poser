#ifndef POSER_BFLT_H
#define POSER_BFLT_H

typedef float f32;
#define f32_size sizeof(f32) //4
#define f32_inf (__builtin_inf())
#define f32_nan (((f32) 0.0) / ((f32) 0.0))

typedef double f64;
#define f64_size sizeof(f64) //8
#define f64_inf (__builtin_inff())
#define f64_nan (((f64) 0.0) / ((f64) 0.0))

typedef long double f128;
#define f128_size sizeof(f128); //16
#define f128_inf (__builtin_infl())
#define f128_nan (((f128) 0.0) / ((f128) 0.0))


#endif