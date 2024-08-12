
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

u0 _printargs(int count, ...) {
    struct va_list_c ap = va_init(count);

    int fmtCount = count - 1;

    char *ptrs[fmtCount];
    char *cfmt = NULL;
    int i;
    for (i = 0; i < ap.count; i++) {
        if (i == 0) {
            cfmt = va_arg(ap.list, char *);
            continue;
        }
        char *str = va_arg(ap.list, char*);
        ptrs[i - 1] = str;
    }

    fstr *fmt = fstr_from_C(cfmt);

    int v = 0;
    for (; v < fmtCount; v++) {
        //replace {v} with arg
        char buf[3 + 2 + 1];
        i64_into_buf(buf, v);

        $ x = "{";
        x = $append(x, buf);
        x = $append(x, "}");

        fstr_replace_C(fmt, x, ptrs[v]);
        hfree(ptrs[v]);
    }

    char *heap = fstr_as_C_heap(fmt);
    put_s(heap);
    hfree(heap);

    fstr_free(fmt);
}


#define printargs(...) _printargs(COUNT_ARGS(__VA_ARGS__), WRAP_S(__VA_ARGS__))

u8 entry() {

    printargs(": Yipee :\n");
    printargs(": {0} :\n", 10);
    printargs(": {0} {1} :\n", 10, 200000000);
    printargs(": {0} {1} {2} :\n", 10, 200, "aa");
    printargs(": {0} {1} {2} {3} :\n", 10, -2000000000, "aa", "zz");
    printargs(": {0} {1} {2} {3} {4} :\n", 10, 200, "aa", "zz", -100);
    printargs(": {0} {1} {2} {3} {4} {5} {6} :\n", 10, 200, "aa", "zz", -100, -99, NULL);
//    printargs(": {0} {1} {2} {3} {4} {5} :\n", 10, 200, "aa", "zz", -100, 99);

    return 1;
}


//entry
