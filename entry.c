
#include "poser/poser.h"
#include "poser/str/m_to_str.h"
#include "poser/comp/arg_inf.h"
#include "poser/sys/sleep.h"
#include "poser/thrd/thrd.h"
#include "poser/fstr/fstr.h"


TUPLE_FUNC({
               u8 _x;
               u8 _y;
           }, function_call)(int x, int y) {
    return (function_call_result_t) {100, 90};
}

/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 */


u8 _test(int count, ...) {

    struct va_list_c ap = va_init(count);

    int i;

    for (i = ap.count; i > 0; i--) {
        i64 x = va_arg(ap.list, int);
        put_u64(x);
        put_s(" ");
    }

    va_end(ap.list);
}

//TODO Logic should generally get split between heap strings and stack strings.

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

u0 _printargs(int count, ...) {
    struct va_list_c ap = va_init(count);

    int fmtCount = count - 1;

    char *strPtrs_array[fmtCount];
    char *cfmt = NULL;

    int i = 0;
    for (; i < ap.count; i++) {
        if (i == 0) {
            cfmt = va_arg(ap.list, char *);
            continue;
        }
        char *str = va_arg(ap.list, char*);
        strPtrs_array[i - 1] = str;
    }

    fstr *res = fstr_fmt_str_args(cfmt, strPtrs_array, fmtCount);
    fstr_print(res);
    fstr_free(res);

    int v = 0;
    for (; v < fmtCount; v++) {
        hfree(strPtrs_array[v]);
    }


    hfree(cfmt);

    va_end(ap.list);
}


#define put_f(...) _printargs(COUNT_ARGS(__VA_ARGS__), WRAP_S(__VA_ARGS__))

u8 entry() {

    while (1) {

        put_f(": Yipee :\n");
        put_f(": {0} :\n", 10);
        put_f(": {0} {1} :\n", 10, 200000000);
        put_f(": {0} {1} {2} :\n", 10, 200, "aa");
        put_f(": {0} {1} {2} {3} :\n", 10, -2000000000, "aa", "zz");
        put_f(": {0} {1} {2} {3} {4} :\n", 10, 200, "aa", "zz", -100);
        put_f(": {0} {1} {2} {3} {4} {5} {6} :\n", 10, 200, "aa", "zz", -100, -99, NULL);
        put_f(": Yipee -------------------------------------------------------------------------------------------------------------------------------------------------------- :\n");
        sleep_ms(100);
    }

    //TODO need console clearing function

//    put_f(": {0} {1} {2} {3} {4} {5} :\n", 10, 200, "aa", "zz", -100, 99);

    return 1;
}


//entry
