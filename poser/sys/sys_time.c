//
// Created by tobin on 2024-08-21.
//

#include "sys_time.h"

u64 sys_get_time_us() {
    u64 result = 0;

#if SYS_OS == OS_WIN
    LARGE_INTEGER ticks;
    LARGE_INTEGER freq;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&ticks);
    i64 total = ticks.QuadPart;

    result = (u64) (((f128) total * 1000000.0) / (f128) freq.QuadPart);
#endif

    return result;
}

u64 sys_get_time_ms() {
    return sys_get_time_us() / 1000;
}

u64 sys_get_time_s() {
    return sys_get_time_us() / 1000 / 1000;
}
