#include "poser/poser.h"
#include "poser/fstr/fstr_to_stack.h"
#include "poser/sstr/sstr_ext.h"
#include "poser/sstr/test.h"

/* Requirements for put_f:
 * USE typeof() to handle type safe printing
 * Maybe make use of function pointers to allow for expanding the type printing?
 */
//TODO implement put_fn {} without number, autoincrement and allow mixing

void print() {
    char* x = "aaa";
    put_f(x);
}

u8 entry() {
    // printf("%d", 10);
    // put_fn("{0}", 10);
    // put_fn("{0}{0}{0}", 10);

    result_file_t x = file_open("testxyz.txt", F_OPEN_RWC);

    put_fn("{0}", x.success);
    put_fn("{0}", x.failureCode);
    put_fn("{0}", x.systemFailureCode);

    u64 c;

    int written = 0;
    $ altbuf = "------";
    WriteFile(x.value.handle, altbuf, str_len(altbuf), &c, NULL);
    written += str_len(altbuf);

    written = SetFilePointer(x.value.handle, 0, NULL, FILE_END);
    put_fn("{0}", written);

    $ buf = "//";
    WriteFile(x.value.handle, buf, str_len(buf), &c, NULL);

    return 1;
}
