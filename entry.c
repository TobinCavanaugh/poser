#include "poser/poser.h"
#include "poser/fstr/fstr_to_stack.h"
#include "poser/sstr/sstr_ext.h"

/*
TUPLE_FUNC({ u8 _x; u8 _y; }, function_call)(int x, int y) {
    return (function_call_result_t) {100, 90};
}
*/

/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 */
//TODO: Allow for {} to auto index in put_f

u0 put_xx() {
    put_sn(fmt_to_sstr("{0} {1} {2} {3}", 1, "zz", 120, 55));
}


/*TODO Branch between stack and heap put_f*/

u8 entry() {

    while (1) {
        put_xx();
    }

    //TODO benchmark echo vs put_s speeds lol
//    sys_command("echo hi");


    return 1;
}