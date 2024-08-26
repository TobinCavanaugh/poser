//
// Created by tobin on 2024-08-13.
//
#include "../fstr/fstr.h"
#include "../dialect.h"
#include "../comp/va_args.h"
#include "../comp/va_init.h"

#ifndef POSER_FMT_TO_FSTR_H
#define POSER_FMT_TO_FSTR_H

/// Counts the arguments and wraps arguments in to_str macro, then calls _fmt_to_fstr
#define fmt_to_fstr(...) _fmt_to_fstr(COUNT_ARGS(__VA_ARGS__), WRAP_S(__VA_ARGS__))

fstr *fstr_fmt_str_args(char *cFmt, char **strPtrs_array, u64 strPtrsCount);

fstr *_fmt_to_fstr(int count, ...);


/*TODO get error handling etc.*/
/* THANKS JESUS! */
#define fmt_to_sstr(...) ({                          \
                                                     \
    PRAG_PUSH;                                       \
    u8 allCount = COUNT_ARGS(__VA_ARGS__);           \
    m_to_str_t* allArgs[] = {WRAP_S(__VA_ARGS__)};   \
                                                     \
    char * fmt = allArgs[0]->buf;                    \
                                                     \
    i8 count = allCount - 1;                         \
                                                     \
    m_to_str_t * strPtrs_array[allCount - 1];        \
    int x = 0;                                       \
    for(; x < count; x++){                           \
        strPtrs_array[x] = allArgs[x + 1];           \
    }                                                \
                                                     \
    $ repl = $append(NULL, fmt);                     \
    char buf[3 + 2 + 1] = "{xxx}";                   \
    u8 xx = 0;                                       \
    for(; xx < count; xx++){                         \
        i64_into_buf(buf, xx);                       \
                                                     \
        $ t = "{";                                   \
        t = $append(t, buf);                         \
        t = $append(t, "}");                         \
                                                     \
        repl = $replace(repl, t, strPtrs_array[xx]->buf); \
    }                                                \
                                                     \
    int v = 0;                                       \
    for(; v < allCount; v++){                        \
        if(!allArgs[v]->isStack){                    \
            hfree(allArgs[v]);                       \
        }                                            \
    }                                                \
                                                     \
    PRAG_POP;                                                 \
    repl;                                            \
})

#endif //POSER_FMT_TO_FSTR_H
