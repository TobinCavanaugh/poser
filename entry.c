#include "poser/poser.h"
#include "poser/fstr/fstr_to_stack.h"
#include "poser/sstr/sstr_ext.h"
#include "poser/sstr/test.h"

/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 */
//TODO: Allow for {} to auto index in put_f

u8 entry() {
    test_all();
    put_fn("{0}{1}{2}", 10, "aa", 30);

    return 1;
}
