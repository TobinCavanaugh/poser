//
// Created by tobin on 2024-08-08.
//

#if SYS_OS == OS_WIN

#include <synchapi.h>

#endif

#include "sleep.h"
#include "../comp/comp.h"

u0 sleep_us(u64 us) {
    HANDLE timer;
    LARGE_INTEGER due_time;

    //Convert to
    due_time.QuadPart = (u64) (-10 * us);

    timer = CreateWaitableTimer(null, true,
                                null);

    SetWaitableTimer(timer, &due_time, 0,
                     NULL,
                     NULL,
                     false);

    WaitForSingleObject(timer, u32_max);
    CloseHandle(timer);
}

u0 sleep_ms(u64 ms) {
#if SYS_OS == OS_WIN
    Sleep(ms);
#else
    assertn(false, "NOT IMPLEMENTED");
#endif
}

u0 sleep_s(u64 s) {
    sleep_ms(s * 1000);
}
