//
// Created by tobin on 7/2/2024.
//

#ifndef POSER_PUTS_H
#define POSER_PUTS_H

#include "../dialect.h"
#include "../str/str.h"

/// Write a string to the stdout
/// \param str The string
/// \return
INLINE u0 put_s(char *str);

INLINE u0 put_sn(char *str);

INLINE u0 put_n();

INLINE u0 put_hs(hstr *str);

u0 put_hsn(hstr * str);

#endif //POSER_PUTS_H
