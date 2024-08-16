//
// Created by tobin on 2024-07-27.
//

#include "../dialect.h"
#include "../fstr/fstr.h"
#include "../str/fmt_to.h"
#include "../str/m_args_wrapper.h"

#define put_f(...) ({ fstr * a = fmt_to_fstr(__VA_ARGS__); fstr_print(a); fstr_free(a); })
#define put_fn(...) ({ fstr * a = fmt_to_fstr(__VA_ARGS__); fstr_println(a); fstr_free(a); })

#ifndef POSER_PUT_F_H
#define POSER_PUT_F_H


#endif //POSER_PUT_F_H
