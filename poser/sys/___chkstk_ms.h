//
// Created by tobin on 2024-07-26.
//

#ifndef POSER____CHKSTK_MS_H
#define POSER____CHKSTK_MS_H

#include "../dialect.h"
#include "sys_plat.h"
#include "sys_exit.h"

#if SYS_OS == OS_WIN
#include <windows.h>
#endif

u0 ___chkstk_ms(u0);

#endif //POSER____CHKSTK_MS_H
