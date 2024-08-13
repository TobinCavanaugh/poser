//
// Created by tobin on 2024-07-26.
//

#ifndef POSER_VA_INIT_H
#define POSER_VA_INIT_H

#include "../poser.h"
#include "va_args.h"

/* The variable passed into count MUST be the last argument in the parent
 * functions argument list. DO NOT use a value that includes a
 * increment/decrement operator. This will explode everything and you will want
 * to die.
 * Performs a va_start and returns a struct va_list_c */
#define va_init(count) ({                           \
    u8 count_val = count;                           \
    va_list list_name;                              \
    va_start(list_name, count);                     \
    struct va_list_c vlc = {list_name, count_val};  \
    /*return*/ vlc;                                 \
})

struct va_list_c {
    va_list list;
    u8 count;
};

#endif //POSER_VA_INIT_H