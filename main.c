#include "io.h"
#include "bint.h"
#include "put.h"
#include "dialect.h"


TUPLE_FUNC({
               u8 _x;
               u8 _y;
           }, function_call)(int x, int y) {
    return (function_call_result) {100, 90};
}


u8 entry() {
    var a = function_call(20, 30);

    put_n();
    put_sn(":)");
    put_n();

    return 0;
}


//entry