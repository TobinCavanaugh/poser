//
// Created by tobin on 7/3/2024.
//
#include "hstr.h"
#include "str.h"
#include "../mem/mem_move.h"
#include "../dialect.h"
#include "../comp/comp.h"

#ifndef POSER_M_TO_STR_H
#define POSER_TO_STR_H

hstr_t *u64_to_hstr(u64 val);

hstr_t *i64_to_hstr(i64 val);

u0 i64_into_buf(chr *buf, i64 val);

u0 u64_into_buf(chr *buf, u64 val);

u0 f128_into_buf(char * buf, u16 buf_len, f128 val);

#endif //POSER_M_TO_STR_H
