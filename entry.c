#include "poser/poser.h"
#include "poser/fstr/fstr_to_stack.h"
#include "poser/sstr/sstr_ext.h"

/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 */
//TODO: Allow for {} to auto index in put_f

//TODO Suboptimal

/*TODO Branch between stack and heap put_f*/

u8 entry() {

    //TODO fix put_fn

    u64 before = sys_get_time_us();

    put_fn(":{0}:", (u8) -1);
    put_fn(":{0}:", (i8) -1);
    put_fn(":{0}:", (u16) -1);
    put_fn(":{0}:", (i16) -1);
    put_fn(":{0}:", (u32) -1);
    put_fn(":{0}:", (i32) -1);
    put_fn(":{0}:", (u32) -1);
    put_fn(":{0}:", (i32) -1);

    while(1){
        put_fn("{0}:{0}:{0}", sys_get_page_size());
//        put_fn("{0}:{1}:{2}", 100, "aa", 300);
//        put_f("{0}--{1}--{2}", "Abcd", 100, 555);

    }
//TODO benchmark echo vs put_s speeds lol
//    sys_command("echo hi");

    return 1;
}