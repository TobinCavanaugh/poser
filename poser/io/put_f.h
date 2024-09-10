//
// Created by tobin on 2024-07-27.
//

#include "../dialect.h"
#include "../fstr/fstr.h"
#include "../str/fmt_to.h"
#include "../str/m_args_wrapper.h"


#define put_f(...) ({ u0 _put_fs_ () { put_s(fmt_to_sstr(__VA_ARGS__)); } _put_fs_(); })
#define put_fn(...) ({ put_f(__VA_ARGS__); put_n(); })

#ifndef POSER_PUT_F_H
#define POSER_PUT_F_H

#endif //POSER_PUT_F_H
