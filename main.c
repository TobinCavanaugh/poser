#include "poser/poser.h"
#include "poser/sys/sysinf.h"
#include "poser/io/put.h"

TUPLE_FUNC({u8 _x; u8 _y;}, function_call)(int x, int y) {
    return (function_call_result){100, 90};
}

#define salloc(size) ({u8 tmp[size]; tmp;})

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
    u8 x = 10;
    x += 10;
    put_hsn(i64_to_hstr((i64)x));

    //Am i in a parallel universe again? I can't mess with stack memory without
    //things breaking immediately. Tested with a different project, we hopped
    //worlds again boys, just like when scoping changed magically... or im an
    //idiot. remember blender image texture output?
    // char* tmp = "0123";
    // char* msg = "4321";
    // // mem_copy(tmp, msg, 4);
    // // tmp[0] = msg[0];
    // tmp[0] = 'a';
    // put_s(tmp);

    int i = 15;
    for (; i > 3; i--)
    {
        ///arggghghghhg... so close
        // char* set = allocs(i + 1);

        // u8 tmp[i + 1];
        // char * set = tmp;
        // u8* set = salloc(i + 1);
        u8* set = halloc(i + 1);
        // u8* set = sa(16);
        // u8* set = halloc(i + 1);

        char* msg = "0123456789012345678901234567890123456789";

        mem_copy(set, msg, i);
        set[i] = '\0';
        put_sn(set);

        hfree(set);
    }

    // put_hsn(i64_to_hstr(25));
    // put_hsn(i64_to_hstr(-25));
    // put_hsn(i64_to_hstr(-5215));
    // put_hsn(i64_to_hstr(-765070));
    // put_hsn(i64_to_hstr(142778421789142));

    return 0;
}


//entry
