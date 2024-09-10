//
// Created by tobin on 2024-08-21.
//

#include "../dialect.h"

#if SYS_OS == OS_WIN

#include <windows.h>

#endif

#ifndef POSER_SYS_TIME_H
#define POSER_SYS_TIME_H

u64 sys_get_time_us();

u64 sys_get_time_ms();

u64 sys_get_time_s();

f64 sys_get_time_sf64();

#endif //POSER_SYS_TIME_H
