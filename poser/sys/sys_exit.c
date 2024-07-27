//
// Created by tobin on 2024-07-26.
//

#if SYS_OS == OS_WIN

#include <processthreadsapi.h>

#endif

#include "sys_exit.h"
#include "sys_plat.h"

u0 sys_exit(u64 code) {

#if SYS_OS == OS_WIN
    ExitProcess(code);
#endif

    //TODO No clue if this works
#if SYS_OS == OS_LINUX
    asm volatile(
            "mov $60, %%rax\n\t"
            "mov $0, %%rdi\n\t"
            "syscall"
            :: "r"(code) : "rax", "rdi"
            );
#endif

}
