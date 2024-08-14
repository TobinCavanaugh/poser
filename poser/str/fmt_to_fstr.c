//
// Created by tobin on 2024-08-13.
//

#include "fmt_to_fstr.h"

fstr *fstr_fmt_str_args(char *cFmt, char **strPtrs_array, u64 strPtrsCount) {
    fstr *fmt = fstr_from_C(cFmt);

    u8 v = 0;
    static char buf[3 + 2 + 1] = "{xxx}";

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
    struct va_list_c ap = va_init(count);

    int fmtCount = count - 1;

    // I ♥ VLAs
    char *strPtrs_array[fmtCount];

    //Our format is always the 1st arg
    char *cfmt = va_arg(ap.list, char *);

    //Iterate all others and place them in the strPtrs array
    int i = 1;
    for (; i < ap.count; i++) {
        char *str = va_arg(ap.list, char*);
        strPtrs_array[i - 1] = str;
    }

    //Perform our actual string formatting here
    fstr *res = fstr_fmt_str_args(cfmt, strPtrs_array, fmtCount);

    int v = 0;
    for (; v < fmtCount; v++) {
        hfree(strPtrs_array[v]);
    }


    hfree(cfmt);

    va_end(ap.list);
//    fstr_print(res);
//    fstr_free(res);
    return res;
}
