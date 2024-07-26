/*
 * Created by tobin on 2024-07-26.
 * Stupid macros to steal gcc's varargs implementation
*/

#ifndef POSER_VA_ARGS_H
#define POSER_VA_ARGS_H

typedef __builtin_va_list va_list;
#define va_start(v, l)    __builtin_va_start(v,l)
#define va_end(v)    __builtin_va_end(v)
#define va_arg(v, l)    __builtin_va_arg(v,l)
#define va_copy(d, s)    __builtin_va_copy(d,s)

#endif //POSER_VA_ARGS_H
