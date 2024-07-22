//
// Created by tobin on 2024-07-21.
//

#include "sysinf.h"


u64 sys_get_page_size() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD pageSize = si.dwPageSize;
    return pageSize;
}
