#include "poser/poser.h"
#include "poser/sys/sysinf.h"
#include "poser/io/put.h"
#include "poser/sstr/sstr.h"

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

//TODO This is stupid but it lets the program compile

void ___chkstk_ms(u64 size) {
    // Do nothing :)
}

// NOTE: hypothetical implementation
// void ___chkstk_ms(u64 frame_size) {
// u64 pageSize = sys_get_page_size();
// volatile char frame[frame_size]; // NOTE: variable-length array
// u64 i = frame_size - pageSize;
// for (; i >= 0; i -= pageSize)
// {
// frame[i] = 0; // touch the guard page
// }
// }

// void ___chkstk_ms(u64 size) {
// __asm__ (
// "push ebp\n\t"
// "mov ebp, esp\n\t"
// "sub esp, %0\n\t" // subtract size from stack pointer
// "cmp esp, dword ptr fs:[0]\n\t" // check if stack pointer is within valid range
// "jb 1f\n\t"
// "mov esp, ebp\n\t"
// "pop ebp\n\t"
// "ret\n\t"
// "1:\n\t"
// "int3\n\t" // raise stack overflow exception (SEH)
// :
// : "r" (size) // input operand: size
// : "ebp", "esp" // clobbered registers
// );
// }

u8 entry() {

    $ str = $from("a");
//    str = $append(str, "aaa");
    str = $append(str, "aa");
    str = $insert(str, 0, "_");

    put_sn(str);

    return 1;

    //^!!! nan f128
    put_hsn(i64_to_hstr(-1238));
    put_hsn(i64_to_hstr(4214142412238));
    put_hsn(i64_to_hstr(-1420104104014421));
    put_hsn(i64_to_hstr(1929465486852383481));
    put_hsn(i64_to_hstr(0));
    put_hsn(i64_to_hstr(-0));
    put_hsn(i64_to_hstr(-1294102948109248124));
    put_hsn(i64_to_hstr(16));


    i64 i = 1;
    while ((i * 10) > i) {
        put_hsn(i64_to_hstr(-i));
        put_s(" ");
        put_hsn(i64_to_hstr(i));

        i *= 10;
    }

    i = 2;
    while ((i * 2) >= i) {
        put_hsn(i64_to_hstr(i));
        put_hsn(i64_to_hstr(-i));
        i *= 2;
    }

    f128 x = 1;
    while (true) {
        f128 prev = x;
        ++x;

        // if (prev > x || prev ==)
        // {
        // break;
        // }
    }

    return 0;
}


//entry
