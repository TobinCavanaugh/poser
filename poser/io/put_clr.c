//
// Created by tobin on 2024-08-14.
//

#include "put_clr.h"

u0 put_clr(){
#if SYS_OS == OS_LINUX
    put_s("\033[2J");
#elif SYS_OS == OS_WIN
    sys_command("cls");
#endif
}
