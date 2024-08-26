//
// Created by tobin on 2024-08-13.
//

#include "fmt_to.h"

fstr *fstr_fmt_str_args(char *cFmt, char **strPtrs_array, u64 strPtrsCount) {
    fstr *fmt = fstr_from_C(cFmt);


//          Parenthesis v
//    Number Length v   v
    static char buf[3 + 2 + 1] = "";

    u8 v = 0;
    for (; v < strPtrsCount; v++) {
        i64_into_buf(buf, v);

        //This is kinda stupid...
        $ x = "{";
        x = $append(x, buf);
        x = $append(x, "}");

        //replace {v} with arg
        fstr_replace_C(fmt, x, strPtrs_array[v]);
    }

    return fmt;
}


fstr *_fmt_to_fstr(int count, ...) {
    int i;
    struct va_list_c ap = va_init(count);

    int fmtCount = count - 1;

    /*I ♥ VLAs*/
    m_to_str_t *m_to_str_array[fmtCount];

    /*Our format is always the 1st arg*/
    m_to_str_t *cfmt = va_arg(ap.list, m_to_str_t *);

    /*Iterate our m_to_str_t*/
    for (i = 0; i < ap.count; i++) {
        m_to_str_t *x = va_arg(ap.list, m_to_str_t *);
        m_to_str_array[i] = x;
    }

    /*Iterate all others and place them in the strPtrs array*/
    char *strPtrs_array[fmtCount];
    for (i = 0; i < fmtCount; i++) {
        strPtrs_array[i] = m_to_str_array[i]->buf;
    }

    /*Perform our actual string formatting here*/
    fstr *res = fstr_fmt_str_args(cfmt->buf, strPtrs_array, fmtCount);

    if (!cfmt->isStack) {
        hfree(m_to_str_array[i]->buf);
    }

    for (i = 0; i < fmtCount; i++) {
        if (!m_to_str_array[i]->isStack) {
            hfree(m_to_str_array[i]->buf);
        }
    }


    va_end(ap.list);
    return res;
}
