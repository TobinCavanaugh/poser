#include "poser/poser.h"

TUPLE_FUNC({
               u8 _x;
               u8 _y;
           }, function_call)(int x, int y) {
    return (function_call_result) {100, 90};
}


u8 entry() {
    var z = function_call(20, 30);

    put_hsn(i64_to_hstr(25));
    put_hsn(i64_to_hstr(-25));
    put_hsn(i64_to_hstr(-5215));
    put_hsn(i64_to_hstr(-765070));
    put_hsn(i64_to_hstr(142778421789142));


    return 0;
}


//entry