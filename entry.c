#include "poser/poser.h"
#include "poser/io/put_f.h"

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


//TODO Logic should generally get split between heap strings and stack strings.

u8 entry() {

    put_fn(": Yipee ");
    put_fn(": {0} ", 10);
    put_fn(": {0} {1} ", 10, 200000000);
    put_fn(": {0} {1} {2} ", 10, 200, "aa");
    put_fn(": {0} {1} {2} {3} ", 10, -2000000000, "aa", "zz");
    put_fn(": {0} {1} {2} {3} {4} ", 10, 200, "aa", "zz", -100);
    put_fn(": {0} {1} {2} {3} {4} {5} {6} ", 10, 200, "aa", "zz", -100, -99, NULL);

//TODO need console clearing function

    return 1;
}