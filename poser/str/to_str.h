//
// Created by tobin on 7/3/2024.
//

#ifndef POSER_TO_STR_H
#define POSER_TO_STR_H

#include "hstr.h"
#include "str.h"
#include "../dialect.h"
#include "../mem/mem_move.h"

hstr* u64_to_hstr(u64 val);

hstr* i64_to_hstr(i64 val);

u0 i64_into_buf(chr* buf, i64 val);

u0 u64_into_buf(chr *buf, u64 val);

#endif //POSER_TO_STR_H
