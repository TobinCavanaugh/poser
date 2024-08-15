//
// Created by tobin on 2024-08-14.
//

#include "../dialect.h"
#include "../comp/comp.h"

#if SYS_OS == OS_WIN
#include <windows.h>
#include <process.h>
#endif


#ifndef POSER_SYS_COMMAND_H
#define POSER_SYS_COMMAND_H

u8 sys_command(char * command);

#endif //POSER_SYS_COMMAND_H
