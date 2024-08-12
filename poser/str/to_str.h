//
// Created by tobin on 7/3/2024.
//

#ifndef POSER_M_TO_STR_H
#define POSER_TO_STR_H

#include "hstr.h"
#include "str.h"
#include "../dialect.h"
#include "../mem/mem_move.h"

hstr_t* u64_to_hstr(u64 val);

hstr_t* i64_to_hstr(i64 val);

u0 i64_into_buf(chr* buf, i64 val);

u0 u64_into_buf(chr *buf, u64 val);

#endif //POSER_M_TO_STR_H
