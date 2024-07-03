//
// Created by tobin on 7/3/2024.
//

#include "mem_set.h"

u0 mem_set(void *start, u8 data, u64 size) {

    u8 *des = start;

    u64 i = 0;
    for (; i < size; i++) {
        des[i] = data;
    }
}
