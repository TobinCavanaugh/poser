#include "poser/sys/sys_plat.h"
#include "poser/poser.h"
#include "poser/sys/sys_inf.h"
#include "poser/io/put.h"
#include "poser/sstr/sstr.h"
#include "poser/mem/mem_set.h"
#include "poser/sys/sys_exit.h"

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


u8 entry() {

    $ str = $from("a");

    str = $append(str, "//");
    str = $insert(str, 0, "_");

    put_sn(str);


    return 1;
}


//entry
