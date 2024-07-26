//
// Created by tobin on 2024-07-21.
//

#ifndef SYS_INF_H
#define SYS_INF_H

#include "../dialect.h"

#if SYS_OS == OS_WIN
#include <windows.h>
#endif


u64 sys_get_page_size();

#endif //SYS_INF_H
