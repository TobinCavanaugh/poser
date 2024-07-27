#include "poser/poser.h"

#define IDE_F_ON /*@formatter:on : clion directive*/
#define IDE_F_OFF /*@formatter:off : clion directive*/

TUPLE_FUNC({ u8 _x; u8 _y; }, function_call)(int x, int y) {
    return (function_call_result) {100, 90};
}

/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 */

#define test(...) _test(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)

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

//#define ifor(varname, max, code) u64 varname = 0; for(; varname < max; varname++) { code; }

u8 entry() {

    test(5, 1, 2, 3, 4, 5);
    put_n();
    test(2, 9, 8, 7, 6, 5, 7, 12, 67);
    put_n();

    return 1;
}


//entry
