//
// Created by tobin on 7/2/2024.
//
#include "../dialect.h"
#include "../mem/mem_copy.h"
#include "hstr.h"

#ifndef POSER_STR_H
#define POSER_STR_H


u64 str_len(char *data);

u64 str_copy(char *dest, char *src);

#endif //POSER_STR_H
