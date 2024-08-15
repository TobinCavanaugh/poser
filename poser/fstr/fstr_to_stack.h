//
// Created by tobin on 2024-08-15.
//

#include "fstr.h"
#include "../mem/mem_copy.h"
#include "../mem/salloc.h"

#ifndef POSER_FSTR_TO_STACK_H
#define POSER_FSTR_TO_STACK_H

#define fstr_to_stack(x) ({u64 xlen = fstr_length(x); char * __data = salloc(xlen + 1); mem_copy(__data, x->data, xlen); __data[xlen] = '\0'; __data;})

#endif //POSER_FSTR_TO_STACK_H
