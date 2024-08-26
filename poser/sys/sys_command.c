//
// Created by tobin on 2024-08-14.
//

#include "sys_command.h"

/// Returns 1 if succeeded, 0 if failed
/// \param command
/// \return
u8 _sys_command(char *command) {
    returnif_(command == NULL, 0);

#if SYS_OS == OS_LINUX
        assertn(0 == 1, "UNIMPLEMENTED");
///https://stackoverflow.com/questions/16398688/how-system-function-in-c-works
#endif

#if SYS_OS == OS_WIN

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    int retVal = 1;
    retVal = CreateProcess(NULL, (LPSTR) command,
                           NULL, NULL,
                           TRUE, 0,
                           NULL, NULL,
                           &si, &pi);

    returnif_(!retVal, 0);

    WaitForSingleObject(pi.hProcess, u32_max);
    GetExitCodeProcess(pi.hProcess, (LPDWORD) &retVal);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 1;
#endif
}

/// Returns 1 if succeeded, 0 if failed. Runs the command as `cmd /c {command}`
/// \param command
/// \return
u8 sys_command(char * command){
    fstr* a = fmt_to_fstr("cmd /c {0}", command);
    _sys_command(fstr_to_stack(a));
    fstr_free(a);
}