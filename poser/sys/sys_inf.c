//
// Created by tobin on 2024-07-21.
//

#include "sys_inf.h"


u64 sys_get_page_size() {

    u64 pageSize = 0;

#if SYS_OS == OS_WIN
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    pageSize = (u64) si.dwPageSize;
#endif

#if SYS_OS == OS_LINUX
    assertn(0 == 1, "NOT IMPLEMENTED");
#endif

    return pageSize;
}
