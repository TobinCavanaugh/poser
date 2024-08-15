//
// Created by tobin on 2024-08-14.
//

#include "sys_command.h"

/// Returns 1 if succeeded, 0 if failed
/// \param command
/// \return
u8 sys_command(char *command) {
    returnif_(command == NULL, 0);
    assertn(0 == 1, "UNIMPLEMENTED");

#if SYS_OS == OS_WIN

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

/*
    u8 res = CreateProcess(NULL,
                           (LPSTR) command,
                           NULL,
                           NULL,
                           0, 0,
                           NULL,
                           NULL,
                           &si,
                           &pi);
*/

//    returnif_(!res, 0);

    WaitForSingleObject(pi.hProcess, u64_max);

    u32 x;
    GetExitCodeProcess(pi.hProcess, &x);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return x;
#endif
}