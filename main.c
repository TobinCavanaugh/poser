#include "poser/poser.h"

TUPLE_FUNC({
               u8 _x;
               u8 _y;
           }, function_call)(int x, int y) {
    return (function_call_result) {100, 90};
}


// inline u8* sa(int size)
// {
// u8* tmp[size];
// return tmp;
// }

#define returnme(a) ({int v = a; v++; v++; v;})


/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 * */


//#define test(...) _test(_NARG(__VA_ARGS__), __VA_ARGS__)

u8 test(int count, ...) {

    struct va_list_c ap = va_init(count);
    int i;

    for (i = ap.count; i > 0; i--) {
        i64 x = va_arg(ap.list, int);
        put_i64(x);
        put_s(" ");
    }

    va_end(ap.list);
}

u8 entry() {

    test(5, 1, 2, 3, 4, 5);
    put_n();
    test(2, 9, 8, 7, 6, 5);

    return 1;

    $ str = $from("a");

    str = $append(str, "//");
    str = $insert(str, 0, "_");

    put_sn(str);

    assert(10 == 20);

    return 1;
}


//entry
