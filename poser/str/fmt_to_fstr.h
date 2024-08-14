//
// Created by tobin on 2024-08-13.
//
#include "../fstr/fstr.h"
#include "../dialect.h"
#include "../comp/va_args.h"
#include "../comp/va_init.h"

#ifndef POSER_FMT_TO_FSTR_H
#define POSER_FMT_TO_FSTR_H

#define fmt_to_fstr(...) _fmt_to_fstr(COUNT_ARGS(__VA_ARGS__), WRAP_S(__VA_ARGS__))

fstr *fstr_fmt_str_args(char *cFmt, char **strPtrs_array, u64 strPtrsCount);

fstr *_fmt_to_fstr(int count, ...);

#endif //POSER_FMT_TO_FSTR_H
