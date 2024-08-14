//
// Created by tobin on 2024-07-26.
//
#include "___chkstk_ms.h"

#if SYS_OS == OS_LINUX
#include <sys/resource.h>
#endif

#if SYS_OS == OS_WIN

#include <processthreadsapi.h>
#include <winternl.h>
#include <intrin.h>

#endif

u64 min_ptr = 0x1000;
u64 max_ptr = 0x7FFFFFFF;

u0 ___chkstk_ms(u0) {

    return;

    // Get the current stack pointer
    u8 x = 0;
    u64 stack_ptr = (u64) &x;


#if SYS_OS == OS_LINUX
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    max_ptr = limit.rlim_max;
#endif

#if SYS_OS == OS_WIN
    GetCurrentThreadStackLimits(&min_ptr, &max_ptr);
#endif

    // Check if the stack pointer is within the allowed range
    if ((stack_ptr) > max_ptr) {
        // Handle stack overflow error
        sys_exit(-1073741571);
    }
    if (stack_ptr < min_ptr) {
        sys_exit(-1073741571);
    }


//    return 1;
//
//    u64 in_RAX;
//    u64 uVar1;
//    u8 *puVar2;
//    u8 local_res8[4];
//    u64 uStack_10;
//
//    puVar2 = local_res8;
//    uVar1 = in_RAX;
//    if (0xfff < in_RAX) {
//        do {
//            puVar2 = puVar2 + -0x200;
//            *puVar2 = *puVar2;
//            uVar1 = uVar1 - 0x1000;
//        } while (0x1000 < uVar1);
//    }
//    uStack_10 = in_RAX;
//    *(u8 *) ((i64) puVar2 - uVar1) = *(u8 *) ((i64) puVar2 - uVar1);
//    return uStack_10;
}
