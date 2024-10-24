//
// Created by tobin on 7/2/2024.
//
#include "../dialect.h"
#include "../str/str.h"
#include "../sstr/sstr.h"
#include "../sstr/sstr_ext.h"
#include "../comp/rare.h"
#include "put_f.h"
#include "../file/file.h"

#ifndef POSER_PUTS_H
#define POSER_PUTS_H



u64 get_stdout_handle();

/// Write a string to the stdout_handle
/// \param str The string
/// \return
POSER_API INLINE u0 put_s(char *str);

POSER_API INLINE u0 put_sn(char *str);

POSER_API INLINE u0 put_n();

POSER_API INLINE u0 put_hs(hstr_t *str);

POSER_API INLINE u0 put_hsn(hstr_t *str);

POSER_API INLINE u0 put_i64(i64 val);

POSER_API INLINE u0 put_i64n(i64 val);

POSER_API INLINE u0 put_u64(u64 val);

POSER_API INLINE u0 put_u64n(u64 val);

POSER_API INLINE u0 write(u64 handle, byte *data, u64 len);

#endif //POSER_PUTS_H
